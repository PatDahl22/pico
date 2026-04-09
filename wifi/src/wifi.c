#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/tcp.h"
#include "lwip/dns.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUTTON_PIN 15
#define SERVER_HOST "192.168.1.135"
#define SERVER_PORT 8080
#define SERVER_PATH "/endpoint"

static volatile bool button_pressed = false;

void button_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON_PIN && (events & GPIO_IRQ_EDGE_FALL)) {
        button_pressed = true;
    }
}

void get_mac_string(char *buf) {
    uint8_t mac[6];
    cyw43_wifi_get_mac(&cyw43_state, CYW43_ITF_STA, mac);
    snprintf(buf, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void send_http_post(const char *mac) {
    char body[64];
    snprintf(body, sizeof(body), "{\"id\":\"%s\"}", mac);

    char request[256];
    snprintf(request, sizeof(request),
             "POST %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Content-Type: application/json\r\n"
             "Content-Length: %d\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%s",
             SERVER_PATH, SERVER_HOST, (int)strlen(body), body);

    struct tcp_pcb *pcb = tcp_new();
    if (!pcb) {
        printf("tcp_new failed\r\n");
        fflush(stdout);
        return;
    }

    ip_addr_t server_ip;
    err_t dns_result = dns_gethostbyname(SERVER_HOST, &server_ip, NULL, NULL);

    if (dns_result == ERR_OK) {
        printf("Sending POST...\r\n");
        fflush(stdout);
        tcp_connect(pcb, &server_ip, SERVER_PORT, NULL);
        tcp_write(pcb, request, strlen(request), TCP_WRITE_FLAG_COPY);
        tcp_output(pcb);
    } else {
        printf("DNS lookup failed: %d\r\n", dns_result);
        fflush(stdout);
    }
}

int main() {
    stdio_init_all();
    sleep_ms(3000);

    if (cyw43_arch_init_with_country(CYW43_COUNTRY_SWEDEN)) {
        printf("WiFi init failed\r\n");
        fflush(stdout);
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to WiFi...\r\n");
    fflush(stdout);

    if (cyw43_arch_wifi_connect_timeout_ms(
            WIFI_SSID,
            WIFI_PASSWORD,
            CYW43_AUTH_WPA2_AES_PSK,
            30000)) {
        printf("WiFi connection failed\r\n");
        printf("SSID: %s\r\n", WIFI_SSID);
        fflush(stdout);
        return 1;
    }

    printf("Connected!\r\n");
    fflush(stdout);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    char mac[18];
    get_mac_string(mac);

    printf("MAC: %s\r\n", mac);
    printf("Ready - press button to send POST\r\n");
    fflush(stdout);

    while (true) {
        if (button_pressed) {
            button_pressed = false;
            send_http_post(mac);
        }
        cyw43_arch_poll();
        sleep_ms(10);
    }
}

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include <stdbool.h>

#define BUTTON_PIN 15

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

void print_ip() {
    uint8_t *ip = (uint8_t*)&cyw43_state.netif[0].ip_addr.addr;
    printf("IP Address: %d.%d.%d.%d\r\n", ip[0], ip[1], ip[2], ip[3]);
}

int main() {
    stdio_init_all();
    sleep_ms(3000); // viktigt för PuTTY

    printf("\r\n=== WIFI START ===\r\n");
    fflush(stdout);

    if (cyw43_arch_init_with_country(CYW43_COUNTRY_SWEDEN)) {
        printf("WiFi init FAILED ❌\r\n");
        fflush(stdout);
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to WiFi: %s\r\n", WIFI_SSID);
    fflush(stdout);

    if (cyw43_arch_wifi_connect_timeout_ms(
            WIFI_SSID,
            WIFI_PASSWORD,
            CYW43_AUTH_WPA2_AES_PSK,
            30000)) {

        printf("WiFi connection FAILED ❌\r\n");
        fflush(stdout);
        return 1;
    }

    printf("WiFi CONNECTED ✅\r\n");
    print_ip();

    char mac[18];
    get_mac_string(mac);
    printf("MAC: %s\r\n", mac);

    printf("System READY - press button 😏\r\n");
    fflush(stdout);

    // setup button
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    uint32_t last_status = 0;

    while (true) {

        // 🔁 status var 5:e sekund
        uint32_t now = to_ms_since_boot(get_absolute_time());
        if (now - last_status > 5000) {
            last_status = now;
            printf("Still connected to WiFi 💚\r\n");
            fflush(stdout);
        }

        // 🔘 knapp
        if (button_pressed) {
            button_pressed = false;
            printf("🔥 BUTTON PRESSED while WiFi active\r\n");
            fflush(stdout);
        }

        cyw43_arch_poll();
        sleep_ms(10);
    }
}

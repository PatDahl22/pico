#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>
#include "hardware/watchdog.h"

#define BUTTON_PIN 15
#define DELAY_MS 250
#define STARTUP_DELAY_MS 6000
#define WATCHDOG_TIMEOUT_MS 5000

volatile bool stop_feeding = false;

void button_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON_PIN && (events & GPIO_IRQ_EDGE_FALL)) {
        stop_feeding = true;
    }
}

static void wait_for_usb_output(void) {
    sleep_ms(2000);
}

int main() {
    stdio_init_all();

    wait_for_usb_output();

    if (watchdog_caused_reboot()) {
        printf("\r\nRecovered from watchdog reset\r\n");
    } else {
        printf("\r\nStarting...\r\n");
    }
    printf("Press button to stop feeding watchdog\r\n");
    fflush(stdout);

    sleep_ms(STARTUP_DELAY_MS);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    watchdog_enable(WATCHDOG_TIMEOUT_MS, 1);

    while (true) {
        if (stop_feeding) {
    	   printf("No dog food!\r\n");
    	   fflush(stdout);
    	   sleep_ms(1000);

    	   while (true) {
              tight_loop_contents();
           }
        }

        printf("Feeding dog\r\n");

        watchdog_update();

        sleep_ms(1000);
    }
}

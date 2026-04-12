#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>

#define BUTTON_PIN 15

volatile bool button_event = false;

void button_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON_PIN && (events & GPIO_IRQ_EDGE_FALL)) {
        button_event = true;
    }
}

int main() {
    stdio_init_all();
    sleep_ms(3000);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    printf("Starting...\r\n");
    fflush(stdout);

    while (true) {
        if (button_event) {
            button_event = false;
            printf("PRESSED\r\n");
            fflush(stdout);
        }
        tight_loop_contents();
    }
}

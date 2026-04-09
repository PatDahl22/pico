#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>

#define LOG_DELAY_MS 250
#define BUTTON_PIN 15

int main() {
    stdio_init_all();

    sleep_ms(3000);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    printf("Starting...\r\n");
    fflush(stdout);

    while (true) {
        bool pressed = !gpio_get(BUTTON_PIN);  // active-low
        printf("Button: %s\r\n", pressed ? "PRESSED" : "released");
        fflush(stdout);
        sleep_ms(LOG_DELAY_MS);
    }
}

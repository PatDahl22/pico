#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef LOG_DELAY_MS
#define LOG_DELAY_MS 250
#endif

int main() {
    stdio_init_all();

    sleep_ms(3000);
    printf("Starting...\r\n");
    fflush(stdout);

    while (true) {
        printf("LED state: %d\r\n", true);
        fflush(stdout);
        sleep_ms(LOG_DELAY_MS);

        printf("LED state: %d\r\n", false);
        fflush(stdout);
        sleep_ms(LOG_DELAY_MS);
    }
}

add_executable(watchdog
    src/watchdog.c
)

target_link_libraries(watchdog
    pico_stdlib
)

pico_enable_stdio_usb(watchdog 1)
pico_enable_stdio_uart(watchdog 0)

pico_add_extra_outputs(watchdog)

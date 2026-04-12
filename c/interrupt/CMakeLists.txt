add_executable(interrupt
    src/interrupt.c
)

target_link_libraries(interrupt
    pico_stdlib
)

pico_enable_stdio_usb(interrupt 1)
pico_enable_stdio_uart(interrupt 0)

pico_add_extra_outputs(interrupt)

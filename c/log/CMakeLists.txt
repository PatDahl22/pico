add_executable(log
    src/log.c
)

target_link_libraries(log
    pico_stdlib
)

pico_enable_stdio_usb(log 1)
pico_enable_stdio_uart(log 0)

pico_add_extra_outputs(log)

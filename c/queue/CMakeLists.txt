add_executable(queue
    src/queue.c
)

target_link_libraries(queue
    pico_stdlib
)

pico_enable_stdio_usb(queue 1)
pico_enable_stdio_uart(queue 0)

pico_add_extra_outputs(queue)

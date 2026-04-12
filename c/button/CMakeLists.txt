add_executable(button
    src/btn.c
)

target_link_libraries(button
    pico_stdlib
)

pico_enable_stdio_usb(button 1)
pico_enable_stdio_uart(button 0)

pico_add_extra_outputs(button)

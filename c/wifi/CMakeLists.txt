add_executable(wifi
    src/wifi.c
)

target_include_directories(wifi PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(wifi
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

pico_enable_stdio_usb(wifi 1)
pico_enable_stdio_uart(wifi 0)

pico_add_extra_outputs(wifi)

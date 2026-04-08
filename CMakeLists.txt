cmake_minimum_required(VERSION 3.12)

set(PICO_BOARD pico2_w CACHE STRING "Target board")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_app C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico_app
    main.c
)

target_link_libraries(pico_app
    pico_stdlib
    pico_cyw43_arch_none
)

pico_add_extra_outputs(pico_app)


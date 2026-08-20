cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(mq135 C CXX ASM)

pico_sdk_init()

add_executable(mq135
    main.c
)

target_link_libraries(mq135
    pico_stdlib
    hardware_adc
    hardware_uart
)

pico_enable_stdio_usb(mq135 1)
pico_enable_stdio_uart(mq135 0)

pico_add_extra_outputs(mq135)

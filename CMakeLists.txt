cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(foo)

pico_sdk_init()

add_executable(foo src/foo.c)

target_include_directories(foo PRIVATE src)

target_link_libraries(foo
    pico_stdlib
    tinyusb_board
    tinyusb_host
)

pico_add_extra_outputs(foo)

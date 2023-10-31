cmake_minimum_required(VERSION 3.13)

set(PROGRAM_NAME robotcar)
set(PICO_BOARD pico_w)

# Pull in Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)


project(${PROGRAM_NAME})

pico_sdk_init()

add_subdirectory(magneto)
add_subdirectory(motor)


# Add the main.c source file to the executable
add_executable(${PROGRAM_NAME}
    main.c
)


target_include_directories(${PROGRAM_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/webserver
    ${CMAKE_CURRENT_LIST_DIR}/magneto
    ${CMAKE_CURRENT_LIST_DIR}/barcode
    ${CMAKE_CURRENT_LIST_DIR}/motor
)

target_link_libraries(${PROGRAM_NAME}
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    pico_stdlib
    hardware_adc
    hardware_pwm
    hardware_i2c
)

pico_enable_stdio_usb(${PROGRAM_NAME} TRUE)
pico_enable_stdio_uart(${PROGRAM_NAME} FALSE)

pico_add_extra_outputs(${PROGRAM_NAME})


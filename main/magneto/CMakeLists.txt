add_executable(magneto magneto.c)

# pull in common dependencies and additional uart hardware support
target_link_libraries(magneto pico_stdlib hardware_i2c)

# enable usb output and uart output
# modify here as required
pico_enable_stdio_usb(magneto 1)
pico_enable_stdio_uart(magneto 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(magneto)

# add url via pico_set_program_url
# example_auto_set_url(magneto)

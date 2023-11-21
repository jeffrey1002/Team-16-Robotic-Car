add_executable(line_detector line_detector.c)

target_link_libraries(line_detector pico_stdlib hardware_adc hardware_pwm)

pico_enable_stdio_usb(line_detector 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(line_detector)

# add url via pico_set_program_url
# example_auto_set_url(line_detector)

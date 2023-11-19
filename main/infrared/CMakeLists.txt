add_executable(infrared line_detector.c)

target_link_libraries(infrared pico_stdlib hardware_adc hardware_pwm)

pico_enable_stdio_usb(infrared 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(infrared)

# add url via pico_set_program_url
# example_auto_set_url(infrared)

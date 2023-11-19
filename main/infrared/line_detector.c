#include "infrared.h"
#include "../motor/motor_control.h"

// variables for tracking motor change state
volatile int line_detector_right = 0;
volatile int line_detector_left = 0;

// initializer
void init_line_detector()
{
    adc_init();
    adc_gpio_init(LINE_DETECTOR_RIGHT_AO);
    adc_gpio_init(LINE_DETECTOR_LEFT_AO);
}

// handler when right IR sensor detects a black line
void line_detect_right(uint slice_num_left, uint slice_num_right)
{
    adc_select_input(LINE_DETECTOR_RIGHT_NUM);
    uint16_t adc_line_right = adc_read();
    float converted_adc_line_right = adc_line_right * ADC_CONVERT;

    if (adc_line_right > THRESHOLD)
    {
        // detected to change motor direction, but state has not changed
        if (line_detector_right == 0)
        {
            // orientate the car to turn left
            spin_left_90(slice_num_left, slice_num_right);
        }

        // update state to know that motor has been changed
        line_detector_right = 1;
    }
    else
    {
        // detected to change motor direction, but state has not changed
        if (line_detector_right == 1)
        {
            // orientate the car back
            spin_right_90(slice_num_left, slice_num_right);
        }

        // update state to know that motor has been changed
        line_detector_right = 0;
    }
}

// handler when left IR sensor detects a black line
void line_detect_left(uint slice_num_left, uint slice_num_right)
{
    adc_select_input(LINE_DETECTOR_LEFT_NUM);
    uint16_t adc_line_left = adc_read();
    float converted_adc_line_left = adc_line_left * ADC_CONVERT;

    if (adc_line_left > THRESHOLD)
    {
        // detected to change motor direction, but state has not changed
        if (line_detector_left == 0)
        {
            // orientate the car to turn right
            spin_right_90(slice_num_left, slice_num_right);
        }

        // update state to know that motor has been changed
        line_detector_left = 1;
    }
    else
    {
        // detected to change motor direction, but state has not changed
        if (line_detector_left == 1)
        {
            // orientate the car back
            spin_left_90(slice_num_left, slice_num_right);
        }

        // update state to know that motor has been changed
        line_detector_left = 0;
    }
}

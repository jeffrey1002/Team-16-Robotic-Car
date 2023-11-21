#include "line_detector.h"
#include "../../motor/motor_control.h"

// line detector initializer
void init_line_detector()
{
    adc_gpio_init(LINE_DETECTOR_RIGHT_AO);
    adc_gpio_init(LINE_DETECTOR_LEFT_AO);
}

// handler when right IR sensor detects a black line
void line_detect_right(uint slice_num_left, uint slice_num_right)
{
    adc_select_input(LINE_DETECTOR_RIGHT_NUM);
    uint16_t adc_line_right = adc_read();
    float converted_adc_line_right = adc_line_right * ADC_CONVERT;

    printf(">>> line at RIGHT: voltage - %f\n", converted_adc_line_right);
    if (converted_adc_line_right > THRESHOLD)
    {
        // detected to change motor direction, but state has not changed
        if (line_detector_right == 0)
        {
            printf(">>> line at RIGHT: detected, car is turning left\n");
            // orientate the car to turn left
            spin_left_45(slice_num_left, slice_num_right);
        }

        // update state to know that motor has been changed
        line_detector_right = 1;
    }
    else
    {
        // detected to change motor direction, but state has not changed
        if (line_detector_right == 1)
        {
            printf(">>> line at RIGHT: car is turning back straight\n");
            // orientate the car back
            spin_right_45(slice_num_left, slice_num_right);
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

    printf(">>> line at LEFT: voltage - %f\n", converted_adc_line_left);
    if (converted_adc_line_left > THRESHOLD)
    {
        // detected to change motor direction, but state has not changed
        if (line_detector_left == 0)
        {
            printf(">>> line at LEFT: detected, car is turning right\n");
            // orientate the car to turn right
            spin_right_45(slice_num_left, slice_num_right);
        }

        // update state to know that motor has been changed
        line_detector_left = 1;
    }
    else
    {
        // detected to change motor direction, but state has not changed
        if (line_detector_left == 1)
        {
            printf(">>> line at LEFT: car is turning back straight\n");
            // orientate the car back
            spin_left_45(slice_num_left, slice_num_right);
        }

        // update state to know that motor has been changed
        line_detector_left = 0;
    }
}

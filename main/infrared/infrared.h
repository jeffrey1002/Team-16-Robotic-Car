#ifndef INFRARED_H
#define INFRARED_H

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

// GPIO pins connected to IR Sensor
#define BARCODE_AO 26
#define LINE_DETECTOR_RIGHT_AO 27
#define LINE_DETECTOR_LEFT_AO 28

// ADC number for respective ADC pins
#define BARCODE_NUM 0
#define LINE_DETECTOR_RIGHT_NUM 1
#define LINE_DETECTOR_LEFT_NUM 2

// ADC voltage converter
#define ADC_VREF 3.3f
#define ADC_RANGE (1 << 12)
#define ADC_CONVERT (ADC_VREF / ADC_RANGE)

// ADC voltage threshold for black line
#define THRESHOLD 0.165f

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

    printf(">>> line at RIGHT: voltage - %f\n", converted_adc_line_right);
    if (converted_adc_line_right > THRESHOLD)
    {
        // detected to change motor direction, but state has not changed
        if (line_detector_right == 0)
        {
            printf(">>> line at RIGHT: detected, car is turning left\n");
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
            printf(">>> line at RIGHT: car is turning back straight\n");
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

    printf(">>> line at LEFT: voltage - %f\n", converted_adc_line_left);
    if (converted_adc_line_left > THRESHOLD)
    {
        // detected to change motor direction, but state has not changed
        if (line_detector_left == 0)
        {
            printf(">>> line at LEFT: detected, car is turning right\n");
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
            printf(">>> line at LEFT: car is turning back straight\n");
            // orientate the car back
            spin_left_90(slice_num_left, slice_num_right);
        }

        // update state to know that motor has been changed
        line_detector_left = 0;
    }
}

#endif
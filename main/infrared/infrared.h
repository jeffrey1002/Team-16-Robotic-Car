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
#define THRESHOLD 0.165


// Function declarations
void init_line_detector();
void line_detect_right(uint slice_num_left, uint slice_num_right);
void line_detect_left(uint slice_num_left, uint slice_num_right);

#endif
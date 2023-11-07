#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "..\headers.h"
#include "..\constants.h"

void encoder_pulse_handler_left();
void encoder_pulse_handler_right();
void initGPIO();
void initialize_motors(uint slice_num_left, uint slice_num_right);

/*****************************
 * Encoder Related Functions *
 *****************************/ 

void speed_and_distance(uint slice_num_left, uint slice_num_right);

/************************************
 * Motor Movement Related Functions *
 ************************************/ 

void spin_right_90(uint slice_num_left, uint slice_num_right);
void spin_left_90(uint slice_num_left, uint slice_num_right);
void fast_forward(uint slice_num_left, uint slice_num_right);
void crawl_forward(uint slice_num_left, uint slice_num_right);
void reverse(uint slice_num_left, uint slice_num_right);
void stop(uint slice_num_left, uint slice_num_right);

/***************************************
 * Ultrasonic Sensor Related Functions *
 ***************************************/ 
float readDistance();

#endif

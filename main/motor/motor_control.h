#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "headers.h"
#include "constants.h"


void encoder_pulse_handler_left();

void encoder_pulse_handler_right();

// Function to initialise GPIO pins
void initGPIO();

// Init for PWM of motors
void initialize_motors(uint slice_num_left, uint slice_num_right);

/*****************************
 * Encoder Related Functions *
 *****************************/ 

void speed_and_distance(uint slice_num_left, uint slice_num_right);


/************************************
 * Motor Movement Related Functions *
 ************************************/ 

// Function to spin the car RIGHT 90 degrees
void spin_right_90(uint slice_num_left, uint slice_num_right);

// Function to spin the car LEFT 90 degrees
void spin_left_90(uint slice_num_left, uint slice_num_right);

void fast_forward(uint slice_num_left, uint slice_num_right);

// Crawl forward is used when obstacle is detected but there's still some distance
void crawl_forward(uint slice_num_left, uint slice_num_right);

void stop(uint slice_num_left, uint slice_num_right);

/***************************************
 * Ultrasonic Sensor Related Functions *
 ***************************************/ 

// Function to read distance from the ultrasonic sensor
float readDistance();

#endif

#ifndef MAGNETO_H
#define MAGNETO_H

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include <string.h>   
#include "hardware/i2c.h"


// Macros
#define MAGNETOMETER_ADDRESS 0x1E
#define CONFIG_REG_A 0x00
#define MODE_REG 0x02
#define DATA_REG_X_MSB 0x03
#define SDA_PIN 0
#define SCL_PIN 1
#define M_PI 3.14159265358979323846

// Function declarations
void custom_i2c_init(i2c_inst_t *i2c);
void write_register(uint8_t reg, uint8_t value);
int16_t read_signed_16bit(uint8_t reg);
float calculate_heading(int16_t x, int16_t y);
void get_direction(float heading, char* direction);

#endif // MAGNETO_H

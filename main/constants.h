#ifndef CONSTANTS_H
#define CONSTANTS_H

// GPIO pins connected to the L298N motor driver
#define MOTOR_ENA 9  // Enable Motor A (GP9) Left motor
#define MOTOR_IN1 10 // Motor A Input 1 (GP10)
#define MOTOR_IN2 11 // Motor A Input 2 (GP11)

#define MOTOR_ENB 8 // Enable Motor B (GP8) Right motor
#define MOTOR_IN3 3 // Motor B Input 1 (GP3)
#define MOTOR_IN4 4 // Motor B Input 2 (GP4)

// GPIO pins connected to the Wheel Encoders
#define ENCODER_CHANNEL_A 12 // Left Wheel Encoder (GP12)
#define ENCODER_CHANNEL_B 7  // Right Wheel Encoder (GP7)

// GPIO pins connected to the Ultrasonic sensor
#define TRIG_PIN 5 // Trigger pin (GP5)
#define ECHO_PIN 6 // Echo pin (GP6)

// Wheel parameters (Physical)
#define WHEEL_CIRCUMFERENCE 22.0  // 22cm
#define ENCODER_PULSES_PER_REVOLUTION 20 // 20 holes in wheel encoder



#endif
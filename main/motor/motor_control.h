#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

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

// Define the GPIO pins connected to the ultrasonic sensor
#define TRIG_PIN 5 // Trigger pin (GP5)
#define ECHO_PIN 6 // Echo pin (GP6)

// Wheel parameters
#define WHEEL_CIRCUMFERENCE 22.0  // in centimeters
#define ENCODER_PULSES_PER_REVOLUTION 20 // Wheel encoder holes

// Variables for tracking distance
volatile int encoder_counts_left = 0;
volatile int encoder_counts_right = 0;

void encoder_pulse_handler_left() {
    // Increment encoder counts for the left wheel when a pulse is detected
    encoder_counts_left++;
}

void encoder_pulse_handler_right() {
    // Increment encoder counts for the right wheel when a pulse is detected
    encoder_counts_right++;
}

// Function to initialise GPIO pins
void initGPIO() {
    // initialise motor pins
    gpio_init(MOTOR_ENA);
    // gpio_set_dir(MOTOR_ENA, GPIO_OUT);

    // Might need to switch the gpio_set_dir to gpio_set_function
    gpio_set_function(MOTOR_ENA, GPIO_FUNC_PWM); // Right Wheel
    
    gpio_init(MOTOR_IN1);
    gpio_set_dir(MOTOR_IN1, GPIO_OUT);

    gpio_init(MOTOR_IN2);
    gpio_set_dir(MOTOR_IN2, GPIO_OUT);

    gpio_init(MOTOR_ENB);
    // gpio_set_dir(MOTOR_ENB, GPIO_OUT);
    gpio_set_function(MOTOR_ENB, GPIO_FUNC_PWM); // Left Wheel

    gpio_init(MOTOR_IN3);
    gpio_set_dir(MOTOR_IN3, GPIO_OUT);

    gpio_init(MOTOR_IN4);
    gpio_set_dir(MOTOR_IN4, GPIO_OUT);

    // initialise PWM for controlling motor speed
    // gpio_set_function(PWM_PIN, GPIO_FUNC_PWM); // Try try

    // initialise ultrasonic sensor pins
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);

    // Initialize GPIO pin for wheel encoder
    gpio_set_dir(ENCODER_CHANNEL_A, GPIO_IN);
    gpio_set_dir(ENCODER_CHANNEL_B, GPIO_IN);

    // Set up an interrupt handler for encoder pulses
    gpio_set_irq_enabled_with_callback(ENCODER_CHANNEL_A, GPIO_IRQ_EDGE_RISE, true, &encoder_pulse_handler_left);
    gpio_set_irq_enabled_with_callback(ENCODER_CHANNEL_B, GPIO_IRQ_EDGE_RISE, true, &encoder_pulse_handler_right);
}

// Init for PWM of motors
void initialize_motors(uint slice_num_left, uint slice_num_right) {

    // Set the clock divider
    pwm_set_clkdiv(slice_num_left, 100);
    // Set the PWM period
    pwm_set_wrap(slice_num_left, 12500);  // Adjust this value as needed for your application
    // Set the PWM running
    pwm_set_enabled(slice_num_left, true);

    // Find out which PWM slice is connected to GPIO 8 (Motor B)
    // slice_num_right = pwm_gpio_to_slice_num(8);
    // Set the clock divider
    pwm_set_clkdiv(slice_num_right, 100);
    // Set the PWM period
    pwm_set_wrap(slice_num_right, 12500);  // Adjust this value as needed for your application
    // Set the PWM running
    pwm_set_enabled(slice_num_right, true);
}

/*****************************
 * Encoder Related Functions *
 *****************************/ 

void speed(uint slice_num_left, uint slice_num_right) {
    // Calculate RPM for both left and right wheels
    float left_wheel_rpm = (encoder_counts_left * 60.0) / (ENCODER_PULSES_PER_REVOLUTION * 0.3); // Update interval is 0.3 seconds
    float right_wheel_rpm = (encoder_counts_right * 60.0) / (ENCODER_PULSES_PER_REVOLUTION * 0.3);

    // Calculate average wheel RPM
    float avg_wheel_rpm = (left_wheel_rpm + right_wheel_rpm) / 2.0;

    // Calculate car speed in centimeters per second
    float car_speed = (avg_wheel_rpm * WHEEL_CIRCUMFERENCE * 3.14159265359) / (ENCODER_PULSES_PER_REVOLUTION * 60.0);

    // Reset encoder_counts for both wheels
    encoder_counts_left = 0;
    encoder_counts_right = 0;

    printf("Car Speed: %.2f cm/s\n\n", car_speed);;
}

/************************************
 * Motor Movement Related Functions *
 ************************************/ 

// Function to spin the car right 90 degrees
void spin_right_90(uint slice_num_left, uint slice_num_right) {

    // target encoder counts for a 90-degree right turn
    int target_counts = 10; // Assuming 20 pulses per revolution

    // Reset the encoder counts
    encoder_counts_right = 0;

    // Wait until the target counts are reached
    while (encoder_counts_right < target_counts)
    {
        // Turn Right
        gpio_put(MOTOR_IN1, 1); // Left
        gpio_put(MOTOR_IN2, 0); // Left
        gpio_put(MOTOR_IN3, 0); // Right
        gpio_put(MOTOR_IN4, 1); // Right

        // Set the PWM duty cycle for right motion
        pwm_set_chan_level(slice_num_right, PWM_CHAN_A, 12500);  // Adjust for motor speed
        pwm_set_chan_level(slice_num_left, PWM_CHAN_B, 12500);

        printf("Turning right >>>>\n");

        sleep_ms(500);  // Spin right for 0.5 second
    }

}

void fast_forward(uint slice_num_left, uint slice_num_right) {
    // Move forward fast
    gpio_put(MOTOR_IN1, 1); // Left
    gpio_put(MOTOR_IN2, 0); // Left
    gpio_put(MOTOR_IN3, 1); // Right
    gpio_put(MOTOR_IN4, 0); // Right

    // Set the PWM duty cycle for forward motion
    pwm_set_chan_level(slice_num_right, PWM_CHAN_A, 12500);  // Adjust for motor speed
    pwm_set_chan_level(slice_num_left, PWM_CHAN_B, 12500);

    speed(slice_num_left, slice_num_right);

    sleep_ms(1000);  // Move forward for 1 second
}

// Crawl forward is used when obstacle is detected but there's still some distance
void crawl_forward(uint slice_num_left, uint slice_num_right) {
    // Move forward slow
    gpio_put(MOTOR_IN1, 1); // Left
    gpio_put(MOTOR_IN2, 0); // Left
    gpio_put(MOTOR_IN3, 1); // Right
    gpio_put(MOTOR_IN4, 0); // Right

    // PWM duty cycle for slow forward motion (80%)
    pwm_set_chan_level(slice_num_right, PWM_CHAN_A, 6250);  // Adjust for motor speed
    pwm_set_chan_level(slice_num_left, PWM_CHAN_B, 6250);

    speed(slice_num_left, slice_num_right);

    sleep_ms(1000);  // Move forward for 1 second
}

void stop(uint slice_num_left, uint slice_num_right) {
    // Move forward fast
    gpio_put(MOTOR_IN1, 0); // Left
    gpio_put(MOTOR_IN2, 0); // Left
    gpio_put(MOTOR_IN3, 0); // Right
    gpio_put(MOTOR_IN4, 0); // Right

    // Set the PWM duty cycle for forward motion
    pwm_set_chan_level(slice_num_right, PWM_CHAN_A, 0);  // Adjust for motor speed
    pwm_set_chan_level(slice_num_left, PWM_CHAN_B, 0);

    speed(slice_num_left, slice_num_right);

    sleep_ms(1000);  // Stop for 1 second
}

/***************************************
 * Ultrasonic Sensor Related Functions *
 ***************************************/ 

// Function to read distance from the ultrasonic sensor
float readDistance()
{
    // Send a trigger pulse
    gpio_put(TRIG_PIN, 1);
    sleep_us(10);
    gpio_put(TRIG_PIN, 0);

    uint64_t width = 0;

    while (gpio_get(ECHO_PIN) == 0)
        tight_loop_contents();
    absolute_time_t startTime = get_absolute_time();
    while (gpio_get(ECHO_PIN) == 1)
    {
        width++;
        sleep_us(1);
    }
    absolute_time_t endTime = get_absolute_time();

    uint64_t distance = absolute_time_diff_us(startTime, endTime);

    // Calculate distance in centimeters
    float distance_cm = (float)(distance * 0.017) / 2.0;
    printf("Obstacle Detected at: %0.1f cm\n", distance_cm);

    return distance_cm;
}


#endif

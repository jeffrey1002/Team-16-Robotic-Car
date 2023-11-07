#include "headers.h" // All headers inside here
#include "constants.h" // All constants inside here

#include "motor/motor_control.h" // Containing L298N motor, Wheel Encoder and Ultrasonic sensor functions
#include "magneto/magneto.h"
#include "wifi.h"


int main() {
        
    while(1){
        init_wifi();
        stdio_init_all(); // Initialise Serial connections
        initGPIO(); // Initialise GPIO pins

        uint slice_num_left = pwm_gpio_to_slice_num(9); // PWM slice connected to GPIO 9 (Left motor)
        uint slice_num_right = pwm_gpio_to_slice_num(8); // PWM slice connected to GPIO 8 (Right motor)
        initialize_motors(slice_num_left, slice_num_right); // Initialise PWM motors

        sleep_ms(2000); // Delay to init everything before run

        // Read distance of nearest obstacle ahead (if any) through the ultrasonic sensor
        float obstacle_distance = readDistance();

        // Check if an obstacle is detected within 30cm
        if (obstacle_distance < 30.0)
        { 
            // if < 30cm, activate crawl mode to approach forward slowly
            crawl_forward(slice_num_left, slice_num_right);
            if (obstacle_distance < 15.0)
            {
                // if obstacle is < 15cm, turn the car 90 degrees to the right
                spin_right_90(slice_num_left, slice_num_right);
                // Reverse car
                reverse(slice_num_left, slice_num_right);
                stop(slice_num_left,slice_num_right);
            }
        }
        else
        {
            // Move forward fast
            fast_forward(slice_num_left, slice_num_right);
        }

    }
}
#include "headers.h" // All headers inside here
#include "constants.h" // All constants inside here

#include "motor/motor_control.h" // Containing L298N motor, Wheel Encoder and Ultrasonic sensor functions
#include "magneto/magneto.h"
#include "wifi.h"


int main() {
        
    while(1){
        init_wifi();
        control_robot();
    }
}
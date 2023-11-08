#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "ssi.h"
#include "cgi.h"

#include "motor_control.h" 

#include "magneto.h"


// http://192.168.10.135/ 

const char WIFI_SSID[] = "Yap Family";
const char WIFI_PASSWORD[] = "98006093";

int main() {
    stdio_init_all();

    cyw43_arch_init();

    cyw43_arch_enable_sta_mode();

    initGPIO();
    uint slice_num_left = pwm_gpio_to_slice_num(9); // PWM slice connected to GPIO 9 (Left motor)
    uint slice_num_right = pwm_gpio_to_slice_num(8); // PWM slice connected to GPIO 8 (Right motor)
    initialize_motors(slice_num_left, slice_num_right); // Initialise PWM motors
    
    sleep_ms(2000); // Delay to init everything before run

    // Connect to the WiFI network - loop until connected
    while(cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) != 0){
        printf("Attempting to connect...\n");
    }
    // Print a success message once connected
    printf("Connected! \n");
    
    // Initialise web server
    httpd_init();
    printf("Http server initialised\n");

    // Configure SSI and CGI handler
    ssi_init(); 
    printf("SSI Handler initialised\n");
    cgi_init();
    printf("CGI Handler initialised\n");

    while (1)
    {
        // Read distance of nearest obstacle ahead (if any) through the ultrasonic sensor
        float obstacle_distance = readDistance();

        // Check if an obstacle is detected within 30cm
        if (obstacle_distance < 30.0)
        { 
            // if < 30cm, activate crawl mode to approach forward slowly
            crawl_forward(slice_num_left, slice_num_right);
            if (obstacle_distance < 15.0)
            {
                stop(slice_num_left,slice_num_right);
            }
        }
        else
        {
            // Move forward fast
            fast_forward(slice_num_left, slice_num_right);
        }
    }

    return 0;
}
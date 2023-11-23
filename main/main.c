#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "motor.h"
#include "lwipopts.h"
#include "ssi.h"
#include "cgi.h"

#include "magneto.h"
#include "barcode/barcode.h"
#include "line_detector/line_detector.h"

// http://192.168.10.135/
// http://192.168.230.42/

const char WIFI_SSID[] = "Phileo's Phone";
const char WIFI_PASSWORD[] = "93803349";

int main()
{
    stdio_init_all();

    cyw43_arch_init();

    cyw43_arch_enable_sta_mode();

    initGPIO(); // Initialise GPIO pins

    uint slice_num_left = pwm_gpio_to_slice_num(9);     // PWM slice connected to GPIO 9 (Left motor)
    uint slice_num_right = pwm_gpio_to_slice_num(8);    // PWM slice connected to GPIO 8 (Right motor)
    initialize_motors(slice_num_left, slice_num_right); // Initialise PWM motors

    adc_init();
    init_barcode();
    init_line_detector();

    sleep_ms(2000); // Delay to init everything before run

    // Connect to the WiFI network - loop until connected
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) != 0)
    {
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
        if (forward == 1)
        {
            // Read distance of nearest obstacle ahead (if any) through the ultrasonic sensor
            // float obstacle_distance = readDistance();

            // Check if there is wall (black line) to change motor direction
            line_detect_right(slice_num_left, slice_num_right);
            line_detect_left(slice_num_left, slice_num_right);

            // Check for barcode
            // scan_barcode();

            // // Check if an obstacle is detected within 30cm
            // if (obstacle_distance < 30.0)
            // {
            //     // if < 30cm, activate crawl mode to approach forward slowly
            //     crawl_forward(slice_num_left, slice_num_right);
            //     if (obstacle_distance < 20.0)
            //     {
            //         // Reverse car
            //         reverse(slice_num_left, slice_num_right);
            //         // if obstacle is < 15cm, turn the car 90 degrees to the right
            //         spin_left_90(slice_num_left, slice_num_right);

            //         stop(slice_num_left, slice_num_right);
            //     }
            // }
            // else
            // {
                // No obstacle detected within 30cm, move forward fast
                fast_forward(slice_num_left, slice_num_right);
            // }
        }
        else
        {
            stop(slice_num_left, slice_num_right);
            line_detector_right = 0; 
            line_detector_left = 0;
        }
    }
    return 0;
}

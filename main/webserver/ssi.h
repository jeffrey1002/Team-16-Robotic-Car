#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "motor_control.h" 


#define POWER_PIN 27

// SSI tags - tag length limited to 8 bytes by default
const char *ssi_tags[] = {"volt", "temp", "robot" , "speed"};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {
    size_t printed;
    switch (iIndex) {
        case 0: // volt
        {
            const float voltage = adc_read() * 3.3f / (1 << 12);
            printed = snprintf(pcInsert, iInsertLen, "%f", voltage);        }
        break;
        case 1: // temp
        {
            const float voltage = adc_read() * 3.3f / (1 << 12);
            const float tempC = 27.0f - (voltage - 0.706f) / 0.001721f;
            printed = snprintf(pcInsert, iInsertLen, "%f", tempC);
        }
        break;
        case 2: // robot
        {
            // Assuming POWER_PIN is used for robot control
            gpio_set_function(POWER_PIN, GPIO_FUNC_SIO);
            
            bool robot_status = gpio_get(POWER_PIN);
            if (robot_status == true) {
                printed = snprintf(pcInsert, iInsertLen, "ON");
            } else {
                printed = snprintf(pcInsert, iInsertLen, "OFF");
            }
        }
        break;
        case 3: // speed
        {
            printed = snprintf(pcInsert, iInsertLen, "%.2f", current_speed);
        }
        break;
        default:
            printed = 0;
            break;
    }

    return (u16_t)printed;
}

// Initialise the SSI handler
void ssi_init() {
    // Initialise ADC (internal pin)
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}

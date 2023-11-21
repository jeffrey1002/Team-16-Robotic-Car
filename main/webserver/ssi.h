#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "motor_control.h" 
#include "barcode.h"

volatile int forward;

// SSI tags - tag length limited to 8 bytes by default
const char *ssi_tags[] = {"volt", "temp", "robot" , "speed" , "dist" , "code"};

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
            if (forward == 1) {
                // If forward is 1, robot is ON
                printed = snprintf(pcInsert, iInsertLen, "ON");
            } else {
                // If forward is not 1, assume robot is OFF
                printed = snprintf(pcInsert, iInsertLen, "OFF");
            }
        }
        break;
        case 3: // speed
        {
            printed = snprintf(pcInsert, iInsertLen, "%.2f", current_speed);
        }
        break;
        case 4: // distance_travelled 
        {
            printed = snprintf(pcInsert, iInsertLen, "%.2f", total_distance_travelled);
        }
        break;
        case 5: // barcode  
        {
            printed = snprintf(pcInsert, iInsertLen, "%.2f", barcode_value);
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

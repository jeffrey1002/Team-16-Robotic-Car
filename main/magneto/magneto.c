#include "magneto.h"

void custom_i2c_init(i2c_inst_t *i2c) {
    printf("[Magnetometer] Init start \n");
    stdio_init_all();
    i2c_init(i2c_default, 100 * 1000); 
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

void write_register(uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};
    i2c_write_blocking(i2c0, MAGNETOMETER_ADDRESS, data, 2, false);
}

int16_t read_signed_16bit(uint8_t reg) {
    uint8_t data[2];
    i2c_write_blocking(i2c0, MAGNETOMETER_ADDRESS, &reg, 1, true);
    i2c_read_blocking(i2c0, MAGNETOMETER_ADDRESS, data, 2, false);
    return (int16_t)((data[0] << 8) | data[1]);
}

float calculate_heading(int16_t x, int16_t y) {
    float heading = atan2(y, x) * (180.0 / M_PI);
    if (heading < 0) heading += 360.0; // Ensure heading is 0-360
    return heading;
}

void get_direction(float heading, char* direction) {
    if (heading >= 45 && heading < 135) {
        strcpy(direction, "E");
    } else if (heading >= 135 && heading < 225) {
        strcpy(direction, "S");
    } else if (heading >= 225 && heading < 345) {
        strcpy(direction, "W");
    } else {
        strcpy(direction, "N");
    }
}

int main() {
    custom_i2c_init(i2c0);

    write_register(CONFIG_REG_A, 0x70); // Set the data output rate
    write_register(MODE_REG, 0x00); // Set continuous-conversion mode
    printf("[Magnetometer] Init done \n");
    sleep_ms(100);

    while (1) {
        int16_t x = read_signed_16bit(DATA_REG_X_MSB);
        int16_t y = read_signed_16bit(DATA_REG_X_MSB + 4);
        int16_t z = read_signed_16bit(DATA_REG_X_MSB + 2);

        float heading = calculate_heading(x, y);
        char direction[2];
        get_direction(heading, direction);

        printf("Magnetometer Data: X=%d, Y=%d, Z=%d, Heading=%.2f, Direction: %s\n", x, y, z, heading, direction);
        sleep_ms(1000);
    }

    return 0;
}

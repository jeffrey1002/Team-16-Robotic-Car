#include "barcode.h"

typedef struct CharacterMapping
{
    char character;
    const char *code39;
} charmap;

// black = 1, white = 0, thick bars = 3 times of thin bar
// total with 3 thick bars and 6 narrow bars
charmap characterMappings[] = {
    {'*', "100010111011101"},
    {'A', "111010100010111"},
    {'B', "101110100010111"},
    {'C', "111011101000101"},
    {'D', "101011100010111"},
    {'E', "111010111000101"},
    {'F', "101110111000101"},
    {'G', "101010001110111"},
    {'H', "111010100011101"},
    {'I', "101110100011101"},
    {'J', "101011100011101"},
    {'K', "111010101000111"},
    {'L', "101110101000111"},
    {'M', "111011101010001"},
    {'N', "101011101000111"},
    {'O', "111010111010001"},
    {'P', "101110111010001"},
    {'Q', "101010111000111"},
    {'R', "111010101110001"},
    {'S', "101110101110001"},
    {'T', "101011101110001"},
    {'U', "111000101010111"},
    {'V', "100011101010111"},
    {'W', "111000111010101"},
    {'X', "100010111010111"},
    {'Y', "111000101110101"},
    {'Z', "100011101110101"}};

void checkThickBar()
{
    // TODO: check the thickness of the bar, e.g. if >= 3 consecutive
    //       detection of the same value, return true
}

int main()
{
    stdio_init_all();
    printf("Barcode detection using ADC, measuring GPIO26\n");

    adc_init();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);

    // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
    const float conversion_factor = 3.3f / (1 << 12);
    float converted_result = 0;

    while (1)
    {
        uint16_t result = adc_read();
        converted_result = result * conversion_factor;
        char *line_color = (converted_result > 0.165) ? "Black" : "White";

        printf("Voltage: %f V, Line Detected: %s\n", converted_result, line_color);

        sleep_ms(150);
        printf("\n\n");
    }
}

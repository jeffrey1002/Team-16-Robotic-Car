#ifndef BARCODE_H
#define BARCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

// GPIO pins connected to IR Sensor
#define BARCODE_AO 26

// ADC number for respective ADC pins
#define BARCODE_NUM 0

// ADC voltage converter
// 12-bit conversion, assume max value == ADC_VREF == 3.3 V
#define ADC_VREF 3.3f
#define ADC_RANGE (1 << 12)
#define ADC_CONVERT (ADC_VREF / ADC_RANGE)

// ADC voltage threshold for black line
#define THRESHOLD 0.165f
// Total number of bars for single char including delimeter
#define TOTAL_BARS 29

// Defined barcode character to send to UI
volatile char barcode_value;

// Total color barcode counted during detection
int black_counter = 0;
int white_counter = 0;
// Total counter, max 29
int total_counter = 0;
// Thickness counter
int thick_counter = 0;
int thin_counter = 0;

int start_to_track = 0; // inital false

// Capture detected barcode
char barcode[16] = {0};

// Structure to store defined barcode code39 characters
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

// Barcode initializer
void init_barcode()
{
    adc_gpio_init(BARCODE_AO);
}

char char_search(const char *substring)
{
    const char *searchSubstring = (substring[0] == '0') ? (substring + 1) : substring;

    // Loop through characterMappings array
    for (size_t i = 0; i < sizeof(characterMappings) / sizeof(characterMappings[0]); ++i)
    {
        if (strstr(characterMappings[i].code39, searchSubstring) != NULL)
        {
            // send value to UI
            barcode_value = characterMappings[i].character;
            return characterMappings[i].character;
        }
    }

    // '0' for detection failure
    return '0';
}

void scan_barcode()
{
    adc_select_input(BARCODE_NUM);
    uint16_t adc_barcode = adc_read();
    float converted_adc_barcode = adc_barcode * ADC_CONVERT;

    // if detected first black, start to scan
    if (converted_adc_barcode > 0.160)
    {
        while (1)
        {
            adc_barcode = adc_read();
            converted_adc_barcode = adc_barcode * ADC_CONVERT;

            // 1 is black, 0 is white
            int line_color_code = (converted_adc_barcode > 0.160) ? 1 : 0;
            // 1 is thick, 0 is thin
            int white_thick_line_code = (converted_adc_barcode < 0.135) ? 1 : 0;
            int black_thick_line_code = (converted_adc_barcode > 0.400) ? 1 : 0;

            // black
            if (line_color_code == 1)
            {
                start_to_track = 1;

                if (white_counter > 0)
                {
                    total_counter += 1;
                    white_counter = 0;

                    // Actual character barcode from 11 - 19
                    if (total_counter >= 11 && total_counter <= 19)
                    {
                        if (thick_counter > thin_counter)
                        {
                            strcat(barcode, "000");
                        }
                        else
                        {
                            strcat(barcode, "0");
                        }
                    }

                    thick_counter = 0;
                    thin_counter = 0;
                }

                black_counter++;

                // thick
                if (black_thick_line_code == 1)
                {
                    thick_counter += 1;
                }
                else
                {
                    thin_counter += 1;
                }
                printf("Voltage: %f V, Line Detected: black %s\n",
                       converted_adc_barcode,
                       (black_thick_line_code == 1) ? "thick" : "thin");
            }
            else // white
            {
                // clear for black
                if (start_to_track == 1)
                {
                    if (black_counter > 0)
                    {
                        total_counter += 1;
                        black_counter = 0;

                        // Actual character barcode from 11 - 19
                        if (total_counter >= 11 && total_counter <= 19)
                        {
                            if (thick_counter > thin_counter)
                            {
                                strcat(barcode, "111");
                            }
                            else
                            {
                                strcat(barcode, "1");
                            }
                        }

                        thick_counter = 0;
                        thin_counter = 0;
                    }

                    white_counter++;

                    // thick
                    if (white_thick_line_code == 1)
                    {
                        thick_counter += 1;
                    }
                    else
                    {
                        thin_counter += 1;
                    }
                    printf("Voltage: %f V, Line Detected: white %s\n",
                           converted_adc_barcode,
                           (white_thick_line_code == 1) ? "thick" : "thin");
                }
            }

            printf("this is the total counter: %d\n", total_counter);

            // reset state and print out detected after 29 bars
            if (total_counter >= TOTAL_BARS)
            {
                start_to_track = 0;
                total_counter = 0;
                printf("this is the stored string: %s\n", barcode);
                printf("this is the determined character: %c\n", char_search(barcode));
                memset(barcode, 0, sizeof(barcode));

                break;
            }

            sleep_ms(1);
            printf("\n\n");
        }
    }
}

#endif

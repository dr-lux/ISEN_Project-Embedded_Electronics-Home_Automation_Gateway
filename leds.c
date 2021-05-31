#include "leds.h"
#include <stdio.h>

void shutdown_led(char* led_path)
{
    FILE* led_file = fopen(led_path, "w"); // Opening led_value's file
    if (led_file != NULL)
    {
        fprintf(led_file, "0"); // Shutdown led
        fclose(led_file); // Closing file
    }
    else
    {
        printf("ERROR : Cannot open %s in function ignite_led\n", led_path);
    }
}

void ignite_led(char* led_path)
{
    FILE* led_file = fopen(led_path, "w"); // Opening led_value's file
    if (led_file != NULL)
    {
        fprintf(led_file, "1"); // Ignite led
        fclose(led_file); // Closing file
    }
    else
    {
        printf("ERROR : Cannot open %s in function ignite_led\n", led_path);
    }
}
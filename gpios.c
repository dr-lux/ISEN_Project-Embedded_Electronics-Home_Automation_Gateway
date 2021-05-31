#include "gpios.h"
#include "defines.h"
#include <stdio.h>
#include <unistd.h>

void GPIO_1to0(int delay1, int delay0)
{
    FILE* qam_in_file = fopen(QAM_PATH, "w");
    if (qam_in_file != NULL)
    {
        // Setting signal to high value
        fprintf(qam_in_file, "1");
        fflush(qam_in_file);
        usleep(delay1);
        // Setting signal to low value
        fprintf(qam_in_file, "0");
        fflush(qam_in_file);
        usleep(delay0);
    }
    else
    {
        printf("ERROR : Cannot open %s in function GPIO_1to0.\n", QAM_PATH);
    }
}

unsigned int read_potentiometer(void)
{
    unsigned int value = 0;
    FILE* file = fopen(POTENTIOMETER_PATH, "r");
    if (file != NULL)
    {
        fscanf(file, "%d", &value);
        fclose(file);
    }
    else
    {
        printf("ERROR : Cannot open %s in function read_potentiometer\n", POTENTIOMETER_PATH);
    }
    return(value);
}

/*
 * On error :
 *  Returns 0 (not '0')
 */
ButtonState read_button()
{
    unsigned char button_value = '1'; // HAVE BETTER THAN CHAR FOR VALUE ?
    FILE* button_file = fopen(BUTTON_PATH, "r");
    if (button_file != NULL)
    {
        fscanf(button_file, "%c", &button_value); // Getting state of button
        fclose(button_file);
    }
    else
    {
        printf("ERROR : Cannot open %s in function read_button\n", BUTTON_PATH);
        return 0;
    }

    if (button_value == '0')
    {
        // CAN YOU KEEP THE FILEPOINT OPEN ?
        // check if the shutdown is asked
        unsigned int loops = 0;
        while (button_value == '1')
        {
            button_file = fopen(BUTTON_PATH, "r");
            if (button_file != NULL)
            {
                fscanf(button_file, "%c", &button_value); // Getting state of button
                fclose(button_file);   
            }
            else
            {
                printf("ERROR : Cannot open %s in function read_button\n", BUTTON_PATH);
                return 0;
            }
            usleep(100);
            loops++;
        }
        // Button pushed during 3 seconds or more statement
        if (loops >= 3000)
        {
            return B_STATE_ALL_OFF;
        }
        // Button pushed during 2 seconds or more statement
        else if (loops >= 2000)
        {
            return B_STATE_ALL_ON;
        }
        // Button pushed during quick time statement
        else
        {
            return B_STATE_LOW;
        }
    }
    else 
    {
        return B_STATE_HIGH;
    }
}
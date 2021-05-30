/*
 * main.c
 *
 *  Created on: May 28, 2021
 *      Author: Titouan Allain
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LED_ID_RED 1
#define LED_ID_GREEN 2
#define LED_ID_BLUE 3

#define LED_PATH_RED "/sys/class/gpio/gpio50/value"
#define LED_PATH_GREEN "/sys/class/gpio/gpio60/value"
#define LED_PATH_BLUE "/sys/class/gpio/gpio3/value"

#define BUTTON_PATH "/sys/class/gpio/gpio48/value"

#define POTENTIOMETER_PATH "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"

#define QAM_PATH "/sys/class/gpio/gpio51/value"

#define T_REF 333

int pushed_button = 0;

char* state_pipe_red = "0";
char* state_pipe_green = "0";
char* state_pipe_blue = "0";

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
        fclose(qam_in_file);
    }
    else
    {
        printf("ERROR : Cannot open %s in function GPIO_1to0.\n", QAM_PATH);
    }
}

void trans_data_433MHz(char data)
{
    switch (data)
    {
        case 'S':
            GPIO_1to0(1 * T_REF, 32 * T_REF); // T1_T32
            break;
        case '0':
            GPIO_1to0(3 * T_REF, 1 * T_REF); // T3_T1
            GPIO_1to0(3 * T_REF, 1 * T_REF); // T3_T1
            break;
        case '1':
            GPIO_1to0(1 * T_REF, 3 * T_REF); // T1_T3
            GPIO_1to0(3 * T_REF, 1 * T_REF); // T3_T1
            break;
        case '2':
            GPIO_1to0(1 * T_REF, 3 * T_REF); // T1_T3
            GPIO_1to0(1 * T_REF, 3 * T_REF); // T1_T3
            break;
        default:
            printf("ERROR : Bad statement with 'data' equal '%c' in function trans_data_433MHz.\n", data);
    }
}

void trans_trame_433MHz(char house, char object, char activation, char repetition)
{
    int nb_repetition = atoi(repetition);
    int repetition_cycle;

    // Transmitting frame
    for (repetition_cycle = 1 ; repetition <= nb_repetition ; repetition_cycle++)
    {
        // Transmitting house's address
        switch(house)
        {
            case 'A':
                trans_data_433MHz('2');
                trans_data_433MHz('1');
                trans_data_433MHz('1');
                trans_data_433MHz('1');
                break;
            case 'B':
                trans_data_433MHz('1');
                trans_data_433MHz('2');
                trans_data_433MHz('1');
                trans_data_433MHz('1');
                break;
            case 'C':
                trans_data_433MHz('1');
                trans_data_433MHz('1');
                trans_data_433MHz('2');
                trans_data_433MHz('1');
                break;
            case 'D':
                trans_data_433MHz('1');
                trans_data_433MHz('1');
                trans_data_433MHz('1');
                trans_data_433MHz('2');
                break;
            default:
                printf("ERROR : Bad statement with 'house' equal '%c' in function trans_trame_433MHz.\n", house);
                return;
        }

        // Transmitting object's address
        switch(object)
        {
            case '1':
                trans_data_433MHz('2');
                trans_data_433MHz('1');
                trans_data_433MHz('1');
                break;
            case '2':
                trans_data_433MHz('1');
                trans_data_433MHz('2');
                trans_data_433MHz('1');
                break;
            case '3':
                trans_data_433MHz('1');
                trans_data_433MHz('1');
                trans_data_433MHz('2');
                break;
            default:
                printf("ERROR : Bad statement with 'object' equal '%c' in function trans_trame_433MHz.\n", object);
                return;
        }

        // Transmitting fixed sequence
        trans_data_433MHz('1');
        trans_data_433MHz('2');
        trans_data_433MHz('1');
        trans_data_433MHz('1');

        // Transmitting activation's state
        switch(activation)
        {
            // Switch off statement
            case '0':
                trans_data_433MHz('2');
                break;
                // Switch on statement
            case '1':
                trans_data_433MHz('1');
                break;
            default:
                printf("ERROR : Bad statement with 'activation' equal '%c' in function trans_trame_433MHz.\n", activation);
                return;
        }

        // Transmitting ending's sequence
        trans_data_433MHz('S');
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

unsigned char read_button()
{
    unsigned char button_value = '0'; // HAVE BETTER THAN CHAR FOR VALUE ?
    FILE* button_file = fopen(BUTTON_PATH, "r");
    if (button_file != NULL)
    {
        fscanf(button_file, "%c", &button_value); // Getting state of button
        fclose(button_file);
    }
    else
    {
        printf("ERROR : Cannot open %s in function read_button\n", BUTTON_PATH);
    }
    return(button_value);
}

void commande_radio(char tube_fluo, char* etat_tube_fluo)
{
    switch (tube_fluo)
    {
        // Red pipe's action statement
        case 'R':
            // Ignite request statement
            if (strcmp(etat_tube_fluo, "1") == 0)
            {
                printf("Ignite the red pipe\n");
                trans_trame_433MHz('C', '1', '1', '9');
            }
                // Shutdown request statement
            else
            {
                printf("Shutdown the red pipe\n");
                trans_trame_433MHz('C', '1', '0', '9');
            }
            break;
            // Green pipe's action statement
        case 'G':
            // Ignite request statement
            if (strcmp(etat_tube_fluo, "1") == 0)
            {
                printf("Ignite the green pipe\n");
                trans_trame_433MHz('B', '1', '1', '9');
            }
                // Shutdown request statement
            else
            {
                printf("Shutdown the green pipe\n");
                trans_trame_433MHz('B', '1', '0', '9');
            }
            break;
            // Blue pipe's action statement
        case 'B':
            // Ignite request statement
            if (strcmp(etat_tube_fluo, "1") == 0)
            {
                printf("Ignite the blue pipe\n");
                trans_trame_433MHz('A', '1', '1', '9');
            }
                // Shutdown request statement
            else
            {
                printf("Shutdown the blue pipe\n");
                trans_trame_433MHz('A', '1', '0', '9');
            }
            break;
            // Error statement
        default:
            printf("ERROR : Bad statement of tube_fluo variable in function commande_radio.\n");
    }
}

void selection()
{
    int selected_color_id;
    unsigned int pot_value = read_potentiometer(); // Reading potentiometer

    // Red LED statement
    if (pot_value < (4095/3)) // < 33%
    {
        shutdown_led(LED_PATH_GREEN);
        shutdown_led(LED_PATH_BLUE);
        ignite_led(LED_PATH_RED);
        selected_color_id = LED_ID_RED;
    }
        // Green LED statement
    else if ((4095/3) <= pot_value && pot_value < (2*4095/3)) // <= 33% and > 66%
    {
        shutdown_led(LED_PATH_RED);
        shutdown_led(LED_PATH_BLUE);
        ignite_led(LED_PATH_GREEN);
        selected_color_id = LED_ID_GREEN;
    }
        // Blue LED statement
    else // <= 66%
    {
        shutdown_led(LED_PATH_RED);
        shutdown_led(LED_PATH_GREEN);
        ignite_led(LED_PATH_BLUE);
        selected_color_id = LED_ID_BLUE;
    }

    // Pushed button statement
    if (read_button() == '0' && pushed_button == 0)
    {
        printf("\n");
        // Invert red pipe statement
        if (selected_color_id == 1)//LED_ID_RED) // NEED TO VERIFY IF THIS DEFINE IS FIXED
        {
            // Switch off statement
            if (state_pipe_red == "1")
            {
                state_pipe_red = "0";
            }
                // Switch on statement
            else
            {
                state_pipe_red = "1";
            }
            commande_radio('R', state_pipe_red);
        }
            // Invert green pipe statement
        else if (selected_color_id == 2)// LED_ID_GREEN)
        {
            // Switch off statement
            if (state_pipe_green == "1")
            {
                state_pipe_green = "0";
            }
                // Switch on statement
            else
            {
                state_pipe_green = "1";
            }
            commande_radio('G', state_pipe_green);
        }
            // Invert blue pipe statement
        else if (selected_color_id == 3)//LED_ID_BLUE)
        {
            // Switch off statement
            if (state_pipe_blue == "1")
            {
                state_pipe_blue = "0";
            }
                // Switch on statement
            else
            {
                state_pipe_blue = "1";
            }
            commande_radio('B', state_pipe_blue);
        }
            // UNREACHABLE CODE
        else
        {
            printf("ERROR : Bad statement of selected_color_id in function selection.\n");
        }
        // END UNREACHABLE CODE
        pushed_button = 1; // Declare we push the button
    }
        // Released button statement
    else if (read_button() == '1' && pushed_button == 1)
    {
        pushed_button = 0; // Declare we've released the button
    }
}



int main()
{
    // Step 2
    /*
	FILE* qam_in_file = fopen(QAM_PATH, "w");
	*/

    while(1)
    {
        // Step 1 & Step 5
        /*
        selection();
        */

        // Step 2
        /*
        // Setting signal to high value
        fprintf(qam_in_file, "1");
        fflush(qam_in_file);
        // Setting signal to low value
        fprintf(qam_in_file, "0");
        fflush(qam_in_file);
        */

        // Step 3
        /*
        // T1_T3
        GPIO_1to0(1 * T_REF, 3 * T_REF);
        // T3_T1
        GPIO_1to0(3 * T_REF, 1 * T_REF);
        // T1_T32
        GPIO_1to0(1 * T_REF, 32 * T_REF);
        */

        // Step 4
        /*
        trans_data_433MHz('2');
        trans_data_433MHz('1');
        trans_data_433MHz('S');
        */
    }
}

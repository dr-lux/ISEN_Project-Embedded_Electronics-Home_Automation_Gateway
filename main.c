/*
 * main.c
 *
 *  Created on: May 28, 2021
 *      Author: Titouan Allain
 */

#include <stdio.h>

#include "defines.h"
#include "gpios.h"
#include "transmission.h"
#include "leds.h"


int pushed_button = 0;

char* state_pipe_red = "0";
char* state_pipe_green = "0";
char* state_pipe_blue = "0";

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
    unsigned char button_state = read_button();
    if (button_state == B_STATE_ALL_ON)
    {
        // set all to on
        trans_trame_433MHz('A', '1', '1', "9");
        trans_trame_433MHz('B', '1', '1', "9");
        trans_trame_433MHz('C', '1', '1', "9");
        trans_trame_433MHz('D', '1', '1', "9");
    }
    else if (button_state == B_STATE_ALL_OFF)
    {
        // set all off
        trans_trame_433MHz('A', '1', '0', "9");
        trans_trame_433MHz('B', '1', '0', "9");
        trans_trame_433MHz('C', '1', '0', "9");
        trans_trame_433MHz('D', '1', '0', "9");
    }
    else if (button_state == B_STATE_LOW && pushed_button == 0)
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
    else if (button_state == B_STATE_HIGH && pushed_button == 1)
    {
        pushed_button = 0; // Declare we've released the button
    }
}



int main(int argc, char** argv)
{
    // Step 2
    /*
	FILE* qam_in_file = fopen(QAM_PATH, "w");
	*/

    // Step 6
    // Connected mode statement
    if (argc == 4)
    {
        // NEED TO ADD SECURITY WHEN WE FINISHED THE PROJECT
        // WARNING -> casting char* to char (argv == char[][], an array of strings)
        trans_trame_433MHz(argv[1][0],argv[2][0],argv[3][0],argv[4]);
    }
    // Autonomous mode statement
    else if (argc <= 1)
    {
        while (1)
        {
            // Step 1 & Step 5 & Step 6
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

    // Error in arguments statement
    else
    {
        printf("ERROR : please enter 0 or 4 arguments for running program.\n");
    }
}

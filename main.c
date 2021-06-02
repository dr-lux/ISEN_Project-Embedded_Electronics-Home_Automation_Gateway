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
#include "thread_led.h"

int pushed_button = 0;

char* state_pipe_red = "0";
char* state_pipe_green = "0";
char* state_pipe_blue = "0";

float duty_red = 0.0;
float duty_green = 0.0;
float duty_blue = 0.0;

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

    // Checking button state
    unsigned char button_state = read_button();

    // Ignite all pipes statements
    if (button_state == B_STATE_ALL_ON)
    {
        // Sending the ignition trame for A1, B1 and C1 pipes
        trans_trame_433MHz('A', '1', '1', "9");
        trans_trame_433MHz('B', '1', '1', "9");
        trans_trame_433MHz('C', '1', '1', "9");
    }
    // Shutdown all pipes statement
    else if (button_state == B_STATE_ALL_OFF)
    {
        // Sending the extinction trame for A1, B1 and C1 pipes
        trans_trame_433MHz('A', '1', '0', "9");
        trans_trame_433MHz('B', '1', '0', "9");
        trans_trame_433MHz('C', '1', '0', "9");
    }
    else if (button_state == B_STATE_LOW && pushed_button == 0)
    {
        printf("\n");
        // Invert red pipe statement
        if (selected_color_id == LED_ID_RED)
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
        else if (selected_color_id == LED_ID_GREEN)
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
        else if (selected_color_id == LED_ID_BLUE)
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
        else
        {
            printf("ERROR : Bad statement of selected_color_id in function selection.\n");
        }
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
    // Calling thread for each LED
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_led, (void *) LED_ID_RED);
    pthread_create(&thread_id, NULL, thread_led, (void *) LED_ID_BLUE);
    pthread_create(&thread_id, NULL, thread_led, (void *) LED_ID_GREEN);

    FILE* qam_in_file = fopen(QAM_PATH, "w");

    // Connected mode statement
    if (argc == 5) // 4 arguments entered
    {
        trans_trame_433MHz(argv[1][0],argv[2][0],argv[3][0],argv[4]);
    }
    // Autonomous mode statement
    else if (argc <= 1)
    {
        // Endless loop
        while (1)
        {
            selection();
        }
    }
    // Arguments error statement
    else
    {
        printf("ERROR : please enter 0 or 4 arguments for running program.\n");
        fclose(qam_in_file);
    }
}
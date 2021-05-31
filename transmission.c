#include "transmission.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "gpios.h"

/*
 * Radio sequences
*/
char A_HOUSE_SEQ[] = {'2','1','1','1'};
char B_HOUSE_SEQ[] = {'1','2','1','1'};
char C_HOUSE_SEQ[] = {'1','1','2','1'};
char D_HOUSE_SEQ[] = {'1','1','1','2'};
char FIXED_SEQ[]   = {'1','2','1','1'};

/*
 * Sends the 'seq' to the radio module (through trans_data_433MHz),
 */
void send_seq(char* seq, size_t count)
{
    if (seq == NULL)
        return;
    
    for (size_t i = 0; i < count; i++)
    {
        trans_data_433MHz(seq[i]);
    }
}

void trans_data_433MHz(char data)
{
    switch (data)
    {
        case 'S':
            GPIO_1to0(1 * T_REF_ADAPTED, 32 * T_REF_ADAPTED); // T1_T32
            break;
        case '0':
            GPIO_1to0(3 * T_REF_ADAPTED, 1 * T_REF_ADAPTED); // T3_T1
            GPIO_1to0(3 * T_REF_ADAPTED, 1 * T_REF_ADAPTED); // T3_T1
            break;
        case '1':
            GPIO_1to0(1 * T_REF_ADAPTED, 3 * T_REF_ADAPTED); // T1_T3
            GPIO_1to0(3 * T_REF_ADAPTED, 1 * T_REF_ADAPTED); // T3_T1
            break;
        case '2':
            GPIO_1to0(1 * T_REF_ADAPTED, 3 * T_REF_ADAPTED); // T1_T3
            GPIO_1to0(1 * T_REF_ADAPTED, 3 * T_REF_ADAPTED); // T1_T3
            break;
        default:
            printf("ERROR : Bad statement with 'data' equal '%c' in function trans_data_433MHz.\n", data);
            break;
    }
}

void trans_trame_433MHz(char house, char object, char activation, char* repetition)
{
    int nb_repetition = atoi(repetition);
    int repetition_cycle;

    // Transmitting frame
    for (repetition_cycle = 1 ; repetition_cycle <= nb_repetition ; repetition_cycle++)
    {
        // Transmitting house's address
        size_t count = 4;
        switch(house)
        {
            case 'A':
                send_seq(A_HOUSE_SEQ, count);
                break;
            case 'B':
                send_seq(B_HOUSE_SEQ, count);
                break;
            case 'C':
                send_seq(C_HOUSE_SEQ, count);
                break;
            case 'D':
                send_seq(D_HOUSE_SEQ, count);
                break;
            default:
                printf("ERROR : Bad statement with 'house' equal '%c' in function trans_trame_433MHz.\n", house);
                return;
        }

        // Transmitting object's address
        char object_seq[4];
        switch(object)
        {
            case '1':
                strcpy(object_seq, "211");
                break;
            case '2':
                strcpy(object_seq, "121");
                break;
            case '3':
                strcpy(object_seq, "112");
                break;
            default:
                printf("ERROR : Bad statement with 'object' equal '%c' in function trans_trame_433MHz.\n", object);
                return;
        }
        send_seq(object_seq, 3);

        // Transmitting fixed sequence
        send_seq(FIXED_SEQ, 4);

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

void commande_radio(char tube_fluo, char* etat_tube_fluo) // NEED TO RENAME IN ENGLISH ALL FRENCH WORD AFTER PROJECT !!!
{
    switch (tube_fluo)
    {
        // Red pipe's action statement
        case 'R':
            // Ignite request statement
            if (strcmp(etat_tube_fluo, "1") == 0)
            {
                printf("Ignite the red pipe\n");
                trans_trame_433MHz('C', '1', '1', "9");
            }
            // Shutdown request statement
            else
            {
                printf("Shutdown the red pipe\n");
                trans_trame_433MHz('C', '1', '0', "9");
            }
            break;
        // Green pipe's action statement
        case 'G':
            // Ignite request statement
            if (strcmp(etat_tube_fluo, "1") == 0)
            {
                printf("Ignite the green pipe\n");
                trans_trame_433MHz('B', '1', '1', "9");
            }
            // Shutdown request statement
            else
            {
                printf("Shutdown the green pipe\n");
                trans_trame_433MHz('B', '1', '0', "9");
            }
            break;
        // Blue pipe's action statement
        case 'B':
            // Ignite request statement
            if (strcmp(etat_tube_fluo, "1") == 0)
            {
                printf("Ignite the blue pipe\n");
                trans_trame_433MHz('A', '1', '1', "9");
            }
            // Shutdown request statement
            else
            {
                printf("Shutdown the blue pipe\n");
                trans_trame_433MHz('A', '1', '0', "9");
            }
            break;
            // Error statement
        default:
            printf("ERROR : Bad statement of tube_fluo variable in function commande_radio.\n");
    }
}
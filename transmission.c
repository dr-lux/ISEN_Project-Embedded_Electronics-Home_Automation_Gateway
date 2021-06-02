#include "transmission.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "gpios.h"

/*
 * Radio sequences
*/
char FIXED_SEQ[]   = {'1','2','1','1'};

char A_HOUSE_SEQ[] = {'2','1','1','1'};
char B_HOUSE_SEQ[] = {'1','2','1','1'};
char C_HOUSE_SEQ[] = {'1','1','2','1'};
char D_HOUSE_SEQ[] = {'1','1','1','2'};
char E_HOUSE_SEQ[] = {'0','0','0','0'};
char F_HOUSE_SEQ[] = {'0','0','0','0'};
char G_HOUSE_SEQ[] = {'0','0','0','0'};
char H_HOUSE_SEQ[] = {'0','0','0','0'};
char I_HOUSE_SEQ[] = {'0','0','0','0'};
char J_HOUSE_SEQ[] = {'0','0','0','0'};
char K_HOUSE_SEQ[] = {'2','1','2','1'};
char L_HOUSE_SEQ[] = {'0','0','0','0'};
char M_HOUSE_SEQ[] = {'0','0','0','0'};
char N_HOUSE_SEQ[] = {'0','0','0','0'};
char O_HOUSE_SEQ[] = {'0','0','0','0'};
char P_HOUSE_SEQ[] = {'0','0','0','0'};

char A_OBJ_SEQ[] = {'2','1','1','1'};
char B_OBJ_SEQ[] = {'1','2','1','1'};
char C_OBJ_SEQ[] = {'1','1','2','1'};
char D_OBJ_SEQ[] = {'1','1','1','2'};
char E_OBJ_SEQ[] = {'0','0','0','0'};
char F_OBJ_SEQ[] = {'0','0','0','0'};
char G_OBJ_SEQ[] = {'0','0','0','0'};
char H_OBJ_SEQ[] = {'0','0','0','0'};
char I_OBJ_SEQ[] = {'0','0','0','0'};
char J_OBJ_SEQ[] = {'0','0','0','0'};
char K_OBJ_SEQ[] = {'2','1','2','1'};
char L_OBJ_SEQ[] = {'0','0','0','0'};
char M_OBJ_SEQ[] = {'0','0','0','0'};
char N_OBJ_SEQ[] = {'0','0','0','0'};
char O_OBJ_SEQ[] = {'0','0','0','0'};
char P_OBJ_SEQ[] = {'0','0','0','0'};


char sequences[16][4];
unsigned int sequencesIt = 0;

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

unsigned int trans_tramev2_433MHz(char house, char object, char activation, char repetition)
{
	char* houseSeq;
	char* objectSeq;
	char state = activation == 1 ? '1' : '2';

	switch(house)
	{
		case 'A':
			houseSeq = A_HOUSE_SEQ;
			break;
		case 'B':
			houseSeq = B_HOUSE_SEQ;
			break;
		case 'C':
			houseSeq = C_HOUSE_SEQ;
			break;
		case 'D':
			houseSeq = D_HOUSE_SEQ;
			break;
		case 'E':
			houseSeq = E_HOUSE_SEQ;
			break;
		case 'F':
			houseSeq = F_HOUSE_SEQ;
			break;
		case 'G':
			houseSeq = G_HOUSE_SEQ;
			break;
		case 'H':
			houseSeq = H_HOUSE_SEQ;
			break;
		case 'I':
			houseSeq = I_HOUSE_SEQ;
			break;
		case 'J':
			houseSeq = J_HOUSE_SEQ;
			break;
		case 'K':
			houseSeq = K_HOUSE_SEQ;
			break;
		case 'L':
			houseSeq = L_HOUSE_SEQ;
			break;
		case 'M':
			houseSeq = M_HOUSE_SEQ;
			break;
		case 'N':
			houseSeq = N_HOUSE_SEQ;
			break;
		case 'O':
			houseSeq = O_HOUSE_SEQ;
			break;
		case 'P':
			houseSeq = P_HOUSE_SEQ;
			break;
		default:
			return ERR_HOUSE_SEQ;
	}

	switch(object)
	{
		case 1:
			objectSeq = A_OBJ_SEQ;
			break;
		case 2:
			objectSeq = B_OBJ_SEQ;
			break;
		case 3:
			objectSeq = C_OBJ_SEQ;
			break;
		case 4:
			objectSeq = D_OBJ_SEQ;
			break;
		case 5:
			objectSeq = E_OBJ_SEQ;
			break;
		case 6:
			objectSeq = F_OBJ_SEQ;
			break;
		case 7:
			objectSeq = G_OBJ_SEQ;
			break;
		case 9:
			objectSeq = H_OBJ_SEQ;
			break;
		case 100:
			objectSeq = I_OBJ_SEQ;
			break;
		case 10:
			objectSeq = J_OBJ_SEQ;
			break;
		case 11:
			objectSeq = K_OBJ_SEQ;
			break;
		case 12:
			objectSeq = L_OBJ_SEQ;
			break;
		case 13:
			objectSeq = M_OBJ_SEQ;
			break;
		case 14:
			objectSeq = N_OBJ_SEQ;
			break;
		case 15:
			objectSeq = O_OBJ_SEQ;
			break;
		default:
			return ERR_OBJECT_SEQ;
	}

	for (char n = 0; n < repetition; n++)
	{
		send_seq(houseSeq, 4);
		send_seq(objectSeq, 4);
		send_seq(FIXED_SEQ, 3);
		trans_data_433MHz(state);
		trans_data_433MHz('S');
	}

	return ERR_SUCCESS;
}

void trans_trame_433MHz(char house, char object, char activation, char repetition)
{
    // Transmitting frame
    for (unsigned int repetition_cycle = 0 ; repetition_cycle < repetition ; repetition_cycle++)
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
        count = 3;
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
        send_seq(object_seq, count);

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
                printf("Turning on the red pipe\n");
                trans_trame_433MHz('C', '1', '1', 9);
            }
            // Shutdown request statement
            else
            {
                printf("Shutting down the red pipe\n");
                trans_trame_433MHz('C', '1', '0', 9);
            }
            break;
        // Green pipe's action statement
        case 'G':
            // Ignite request statement
            if (strcmp(etat_tube_fluo, "1") == 0)
            {
                printf("Turning on the green pipe\n");
                trans_trame_433MHz('B', '1', '1', 9);
            }
            // Shutdown request statement
            else
            {
                printf("Shutting down the green pipe\n");
                trans_trame_433MHz('B', '1', '0', 9);
            }
            break;
        // Blue pipe's action statement
        case 'B':
            // Ignite request statement
            if (strcmp(etat_tube_fluo, "1") == 0)
            {
                printf("Turning on the blue pipe\n");
                trans_trame_433MHz('A', '1', '1', 9);
            }
            // Shutdown request statement
            else
            {
                printf("Shutting down the blue pipe\n");
                trans_trame_433MHz('A', '1', '0', 9);
            }
            break;
            // Error statement
        default:
            printf("ERROR : Bad statement of tube_fluo variable in function commande_radio.\n");
            break;
    }
}

void enumerate(int i, int n, char* array, char combinations[16][4])
{
	if (i == n)
	{
		//printf("{");
		for (int k = 0; k < n; k++)
		{
			//printf(" '%c',", array[k]);
			combinations[sequencesIt][k] = array[k];
		}
		//printf("}\n");
		sequencesIt++;
		return;
	}

	array[i] = '1';
	enumerate(i+1, n, array, combinations);
	array[i] = '2';
	enumerate(i+1, n, array, combinations);
}

void radio_broadcast()
{
	char bigseq[13] = { '2','1','2','1', '2','1','2','1', '2','1','1', '1', 'S' };
	for (int i = 0; i < 9; i++)
		send_seq(bigseq, 13);

	return;


	char combs1[16][4];
    char* seq = (char[4]){ '1', '1', '1', '1' };
    enumerate(0, 4, seq, combs1);

    printf("\n---------------------------------------\n");

    for (int a = 0; a < 16; a++)
	{
		printf("house %d -> {", a);
		for (int c = 0; c < 4; c++)
		{
			printf("%c, ", combs1[a][c]);
		}
		printf("}\n");

		for (int b = 0; b < 16; b++)
		{
			printf("object ->{ ");
			for (int c = 0; c < 4; c++)
			{
				printf("%c, ", combs1[b][c]);
			}
			printf("}\n\n");

			for (size_t rep =0; rep < 10; rep++)
			{
				send_seq(combs1[a], 4);
				send_seq(combs1[b], 4);
				send_seq(FIXED_SEQ, 3);
				trans_data_433MHz('1');
				trans_data_433MHz('S');
			}

			//usleep(500);
		}
	}
}

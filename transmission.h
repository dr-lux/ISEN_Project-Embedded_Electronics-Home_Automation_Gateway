#ifndef TRANSMISSION_H
#define TRANSMISSION_H

void trans_data_433MHz(char data);
void trans_trame_433MHz(char house, char object, char activation, char* repetition);
void commande_radio(char tube_fluo, char* etat_tube_fluo);

#endif
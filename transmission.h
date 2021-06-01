#ifndef TRANSMISSION_H
#define TRANSMISSION_H

/*
 * ERROR : Bad statement with 'house' not recognized in function trans_trame_433MHz.
 */
#define ERR_HOUSE_SEQ  1
/*
 * ERROR : Bad statement with 'object' not recognized in function trans_trame_433MHz.
 */
#define ERR_OBJECT_SEQ 2
/*
 * Success
 */
#define ERR_SUCCESS    0

void trans_data_433MHz(char data);
void trans_trame_433MHz(char house, char object, char activation, char repetition);
unsigned int trans_tramev2_433MHz(char house, char object, char activation, char repetition);
void commande_radio(char tube_fluo, char* etat_tube_fluo);
void radio_broadcast();

#endif

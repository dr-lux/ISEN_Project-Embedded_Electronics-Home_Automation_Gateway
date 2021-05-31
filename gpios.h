#ifndef GPIOS_H
#define GPIOS_H


#define B_STATE_LOW     0
#define B_STATE_HIGH    1
#define B_STATE_ALL_ON  2
#define B_STATE_ALL_OFF 3
typedef unsigned char ButtonState; 

void GPIO_1to0(int delay1, int delay0);
unsigned int read_potentiometer();
ButtonState read_button();

#endif
#ifndef DEFINES_H
#define DEFINES_H

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
#define T_REF_ADAPTED 235

#endif
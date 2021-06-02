#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PERIOD 20000

void* thread_led(void* void_led_id);
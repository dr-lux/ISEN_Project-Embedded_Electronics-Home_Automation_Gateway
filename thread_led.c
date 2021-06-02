#include "thread_led.h"

void* thread_led(void* void_led_id)
{
    char* led_path = (char*) malloc(0);
    int led_id = (int) void_led_id;

    switch (led_id)
    {
        case LED_ID_RED:
            led_path = (char*) realloc(led_path, strlen(LED_PATH_RED) + 1);
            strcpy(led_path, LED_PATH_RED);
            break;
        case LED_ID_GREEN:
            led_path = (char*) realloc(led_path,strlen(LED_PATH_GREEN) + 1);
            strcpy(led_path, LED_PATH_GREEN);
            break;
        case LED_ID_BLUE:
            led_path = (char*) realloc(led_path,strlen(LED_PATH_BLUE) + 1);
            strcpy(led_path, LED_PATH_BLUE);
            break;
        default:
            printf("ERROR : Bad statement of led_id in thread_led.\n");
    }

    FILE* led_file = fopen(led_path,"w");
    if (led_file != NULL)
    {
        while(1)
        {
            fprintf(led_file, "1");
            fflush(led_file);
            switch (led_id)
            {
                case LED_ID_RED:
                    usleep(PERIODE * duty_red);
                    break;
                case LED_ID_GREEN:
                    usleep(PERIODE * duty_green);
                    break;
                case LED_ID_BLUE:
                    usleep(PERIODE * duty_blue);
                    break;
                default:
                    printf("ERROR : Bad statement of led_id in thread_led.\n");
            }
            fprintf(led_file, "0");
            fflush(led_file);
            switch (led_id)
            {
                case LED_ID_RED:
                    usleep(PERIODE * (1 - duty_red));
                    break;
                case LED_ID_GREEN:
                    usleep(PERIODE * (1 - duty_green));
                    break;
                case LED_ID_BLUE:
                    usleep(PERIODE * (1 - duty_blue));
                    break;
                default:
                    printf("ERROR : Bad statement of led_id in thread_led.\n");
            }
        }
    }
    else
    {
        printf("ERROR : Cannot open file %s in thread.\n", LED_PATH_GREEN);
    }
}
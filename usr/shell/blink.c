#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <dev/registers.h>
#include <kernel/sched.h>

#include "blink.h"

void blue_led(void);
void orange_led(void);
void green_led(void);

uint8_t enabled_blue = 0;
uint8_t enabled_orange = 0;
uint8_t enabled_green = 0;

void blink(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s LED...\r\nExample: blink blue orange\r\n", argv[0]);
        return;
    }

    for (int i = 1; i < argc; i++) {
        if (!strncmp(argv[i], "blue", 16)) {
            if (enabled_blue) {
                printf("Blue LED already enabled.\r\n");
            }
            else {
                printf("Enabling blue LED...");
                new_task(&blue_led, 5, 200);
                enabled_blue = 1;
                printf("Done.\r\n");
            }
        }
        else if (!strncmp(argv[i], "orange", 16)) {
            if (enabled_orange) {
                printf("Orange LED already enabled.\r\n");
            }
            else {
                printf("Enabling orange LED...");
                new_task(&orange_led, 5, 800);
                enabled_orange = 1;
                printf("Done.\r\n");
            }
        }
        else if (!strncmp(argv[i], "green", 16)) {
            if (enabled_green) {
                printf("Green LED already enabled.\r\n");
            }
            else {
                printf("Enabling green LED...");
                new_task(&green_led, 5, 400);
                enabled_green = 1;
                printf("Done.\r\n");
            }
        }
        else {
            printf("Unknown LED: %s\r\n", argv[i]);
        }
    }
}

void blue_led(void) {
    /* Toggle LED */
    *LED_ODR ^= (1 << 15);
}

void orange_led(void) {
    /* Toggle LED */
    *LED_ODR ^= (1 << 13);

}

void green_led(void) {
    *LED_ODR ^= (1 << 12);
}

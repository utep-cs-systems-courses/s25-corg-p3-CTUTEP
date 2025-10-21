#include <msp430.h>
#include "led.h"

unsigned char red_brightness = 0;
unsigned char green_brightness = 0;
unsigned char count = 0;

void led_init() {
    P1DIR |= LEDS;        // Set LED pins as outputs
    P1OUT &= ~LEDS;       // Turn off LEDs
}

void led_update() {
    count++;
    // Using count to create PWM effect for brightness levels
    P1OUT &= ~LEDS;       // Turn off both LEDs
    
    // Red LED PWM
    if (count < red_brightness) {
        P1OUT |= LED_RED;
    }
    
    // Green LED PWM
    if (count < green_brightness) {
        P1OUT |= LED_GREEN;
    }
    
    if (count >= 100) {   // Reset counter after 100 cycles
        count = 0;
    }
}

void set_red_brightness(unsigned char brightness) {
    red_brightness = brightness;
}

void set_green_brightness(unsigned char brightness) {
    green_brightness = brightness;
}
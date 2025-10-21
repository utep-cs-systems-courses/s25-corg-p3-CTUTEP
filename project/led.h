#ifndef led_included
#define led_included

#define LED_RED BIT0    // P1.0
#define LED_GREEN BIT6  // P1.6
#define LEDS (LED_RED | LED_GREEN)

void led_init();
void led_update();
void set_red_brightness(unsigned char brightness);
void set_green_brightness(unsigned char brightness);

#endif
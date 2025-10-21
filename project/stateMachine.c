#include <msp430.h>
#include "stateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

char state = STATE_OFF;

extern void state_cycle_asm(); // assembly function

void state_init() {
    state = STATE_OFF;
    set_red_brightness(0);
    set_green_brightness(0);
    buzzer_set_note(4); // silent
}

void apply_state_effects() {
    switch(state) {
        case STATE_OFF:
            set_red_brightness(0);
            set_green_brightness(0);
            buzzer_set_note(4);
            break;
        case STATE_PATTERN1:
            set_red_brightness(100);
            set_green_brightness(30);
            buzzer_set_note(0);
            break;
        case STATE_PATTERN2:
            set_red_brightness(30);
            set_green_brightness(100);
            buzzer_set_note(1);
            break;
        case STATE_PATTERN3:
            set_red_brightness(50);
            set_green_brightness(50);
            buzzer_set_note(2);
            break;
        case STATE_PATTERN4:
            set_red_brightness(80);
            set_green_brightness(80);
            buzzer_set_note(3);
            break;
    }
}

void state_advance() {
    // Called periodically from WDT interrupt
    led_update();
    buzzer_update();

    if (switch_state_changed) {
        switch_state_changed = 0;
        // Button 1 (P2.0) cycles through states using assembly (edge-detected)
        if (switch_pressed[0]) {
            switch_pressed[0] = 0;
            state_cycle_asm();
            apply_state_effects();
        }
        // Button 2 (P2.1) cycles brightness levels (edge-detected)
        if (switch_pressed[1]) {
            switch_pressed[1] = 0;
            // brightness levels: 0, 30, 50, 80, 100
            static const unsigned char levels[] = {0, 30, 50, 80, 100};
            static unsigned char idx = 0;
            idx = (idx + 1) % (sizeof(levels)/sizeof(levels[0]));
            set_red_brightness(levels[idx]);
            set_green_brightness(levels[idx]);
        }
        // Button 3 (P2.2) advance buzzer note (edge-detected)
        if (switch_pressed[2]) {
            switch_pressed[2] = 0;
            buzzer_advance_note();
            buzzer_update();
        }
        // Button 4 (P2.3) reset to OFF (edge-detected)
        if (switch_pressed[3]) {
            switch_pressed[3] = 0;
            state = STATE_OFF;
            apply_state_effects();
        }
    }
}

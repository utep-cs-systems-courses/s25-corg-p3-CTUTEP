#include <msp430.h>
#include "switches.h"

char switch_state_changed = 0;
char switch_states[4] = {0, 0, 0, 0};
char switch_pressed[4] = {0,0,0,0};

// Simple debounce: ignore changes within this many ISR ticks
#define DEBOUNCE_TICKS 30
static unsigned int last_change_tick[4] = {0,0,0,0};
static unsigned int tick_count = 0;

void switch_init() {
    P2REN |= SWITCHES;    // Enable resistors on switches
    P2IE  |= SWITCHES;    // Enable interrupts from switches
    P2OUT |= SWITCHES;    // Pull-ups for switches
    P2DIR &= ~SWITCHES;   // Set switches as inputs
}

// Interrupt handler for Port 2
void __interrupt_vec(PORT2_VECTOR) Port_2() {
    char p2val = P2IN;
    tick_count++; // advance time for debounce

    char new_states[4];
    new_states[0] = (p2val & SW1) ? 0 : 1;
    new_states[1] = (p2val & SW2) ? 0 : 1;
    new_states[2] = (p2val & SW3) ? 0 : 1;
    new_states[3] = (p2val & SW4) ? 0 : 1;

    for (int i = 0; i < 4; ++i) {
        if (new_states[i] != switch_states[i]) {
            // changed state; check debounce
            if ((tick_count - last_change_tick[i]) > DEBOUNCE_TICKS) {
                // register change
                switch_states[i] = new_states[i];
                last_change_tick[i] = tick_count;
                switch_state_changed = 1;
                if (switch_states[i]) { // pressed (active low -> 1 means pressed)
                    switch_pressed[i] = 1; // edge-detected press
                }
            }
        }
    }

    P2IFG &= ~SWITCHES;   // Clear pending interrupts
}

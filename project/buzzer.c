#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

// Define some note frequencies (periods)
#define C4  7382    // ~261.6 Hz
#define D4  6577    // ~293.7 Hz
#define E4  5859    // ~329.6 Hz
#define F4  5530    // ~349.2 Hz
#define G4  4924    // ~392.0 Hz
#define A4  4389    // ~440.0 Hz
#define B4  3910    // ~493.9 Hz
#define C5  3691    // ~523.3 Hz

static int current_note = 0;
static int current_period = 0;

void buzzer_init() {
    timerAUpmode();                    // Used to drive speaker
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7;
    P2SEL |= BIT6;
    P2DIR = BIT6;                      // Enable output to speaker (P2.6)
}

void buzzer_set_period(short cycles) {
    CCR0 = cycles;
    CCR1 = cycles >> 1;                // One half cycle
    current_period = cycles;
}

void buzzer_update() {
    switch(current_note) {
    case 0:
        buzzer_set_period(C4);
        break;
    case 1:
        buzzer_set_period(E4);
        break;
    case 2:
        buzzer_set_period(G4);
        break;
    case 3:
        buzzer_set_period(C5);
        break;
    default:
        buzzer_set_period(0);  // Silent
        break;
    }
}

void buzzer_advance_note() {
    current_note = (current_note + 1) % 5;  // Cycle through 5 states (including silent)
}

void buzzer_set_note(int note) {
    current_note = note % 5;
    buzzer_update();
}

// Function to get current period (useful for state machine)
int buzzer_get_period() {
    return current_period;
}
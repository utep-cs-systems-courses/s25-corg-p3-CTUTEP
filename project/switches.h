#ifndef switches_included
#define switches_included

#define SW1 BIT0    // P2.0
#define SW2 BIT1    // P2.1
#define SW3 BIT2    // P2.2
#define SW4 BIT3    // P2.3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

void switch_init();
void switch_interrupt_handler();

extern char switch_state_changed;
extern char switch_states[4];
// Per-button press-detected flags (edge-detected, debounced)
extern char switch_pressed[4];

#endif
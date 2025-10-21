#include &lt;msp430.h&gt;
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachine.h"

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
    
    // Initialize all components
    led_init();
    switch_init();
    buzzer_init();
    state_init();
    
    enableWDTInterrupts();  // Enable periodic interrupts
    
    or_sr(0x18);  // CPU off, GIE on
}

// Watchdog Timer interrupt handler
void __interrupt_vec(WDT_VECTOR) WDT() {
    // Update state machine periodically
    state_advance();    // This will handle LED and buzzer updates
}
# Blinky-Buzzy Toy

This project implements Lab 2: Blinky-Buzzy Toy for the MSP430G2553.

Features
- Generates sounds via the buzzer (P2.6 / TimerA)
- Dynamically changes LED brightness using software PWM on P1.0 (red) and P1.6 (green)
- Implements a finite state machine with 5 states (OFF + 4 patterns)
- Uses the 4 expansion switches (P2.0..P2.3) to control behavior
- At least one state transition function (`state_cycle_asm`) is written in MSP430 assembly

Build and load

1. From the repo root, build the timer library and install headers/libs used by the project:

    cd demos/timerLib; make install

2. Build the project:

    cd project; make

3. Load the program to the MSP430 (requires `mspdebug`):

    cd project; make load

Usage
- Button P2.0: Cycle toy state (assembly function)
- Button P2.1: Increase brightness (demo behavior)
- Button P2.2: Advance buzzer note
- Button P2.3: Reset to OFF

Hardware test status
--------------------
This code has been implemented and reviewed but not yet flashed to physical MSP430 hardware by the author. The code follows the demo build and timer library conventions; to verify on hardware, follow the Build and load steps above. The project includes simple software debouncing for the switches and a brightness cycling behavior on P2.1.

Notes
- This project expects `msp430-elf-gcc`, `msp430-elf-as`, `msp430-elf-ar`, and `mspdebug` to be installed and on PATH.
- If you are missing the toolchain, compile errors will appear for missing `msp430.h` or other toolchain headers; those are resolved by installing the MSP430 GCC toolchain.

Files of interest
- `main.c` - Initializes hardware and enters low-power mode with WDT interrupts
- `led.c` / `led.h` - Software PWM LED control
- `buzzer.c` / `buzzer.h` - Buzzer control using Timer A
- `switches.c` / `switches.h` - Button initialization and ISR
- `stateMachine.c` / `stateAdvance.s` - State machine and assembly state-cycle function

License
MIT

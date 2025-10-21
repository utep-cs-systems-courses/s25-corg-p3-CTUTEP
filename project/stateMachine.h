#ifndef stateMachine_included
#define stateMachine_included

// State definitions
#define STATE_OFF 0
#define STATE_PATTERN1 1
#define STATE_PATTERN2 2
#define STATE_PATTERN3 3
#define STATE_PATTERN4 4

extern char state;

void state_init();
void state_advance();

#endif
#ifndef buzzer_included
#define buzzer_included

void buzzer_init();
void buzzer_set_period(short cycles);
void buzzer_update();
void buzzer_advance_note();
void buzzer_set_note(int note);
int buzzer_get_period();

#endif
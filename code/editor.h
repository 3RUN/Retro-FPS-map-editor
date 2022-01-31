#ifndef _EDITOR_H_
#define _EDITOR_H_

#define STATE_MENU 0
#define STATE_LOAD 1
#define STATE_NEW 2
#define STATE_EPISODE 3
#define STATE_EDITOR 4
#define STATE_TEST 5

int editor_state = STATE_MENU;
int editor_old_state = STATE_MENU;

void editor_switch_state_to(int state);

void editor_create_tooltip(STRING *tooltip);

void editor_help_maker(char *desc);

#endif
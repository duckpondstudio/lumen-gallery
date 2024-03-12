#ifndef INPUT_H
#define INPUT_H

#include <EasyButton.h>

#define BTN_PIN_SAT 7
#define BTN_PIN_VAL 6

#define BTNS_DEBOUNCE 35
#define BTNS_PULLUP false
#define BTNS_INVERT false

void setupInput();
void loopInput();

bool isPressedSat();
bool isPressedVal();

#endif
#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <SimpleEncoder.h>
// #include <EncoderButton.h>
// #include <Encoder.h>

#include "pindef.h"

#define BTNS_DEBOUNCE 35
#define BTNS_PULLUP false
#define BTNS_INVERT false



void setupInput();
void loopInput();

bool isPressedSat();
bool isPressedVal();
bool isPressedEnc();

byte encoderValueAsByte();
long encoderValue();

#endif
#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <SimpleEncoder.h>
// #include <EncoderButton.h>
// #include <Encoder.h>

#define PIN_BTN_SAT 7
#define PIN_BTN_VAL 6
#define PIN_BTN_ENC 4

#define PIN_ENC_A 2
#define PIN_ENC_B 3

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
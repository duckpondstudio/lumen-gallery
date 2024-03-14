#ifndef INPUT_H
#define INPUT_H

#include <avr/io.h>

#include <Arduino.h>
#include <RotaryEncoder.h>
// #include <OneButtonTiny.h>
#include <Button.h>

#include "pindef.h"

#define BTNS_DEBOUNCE 35
#define BTNS_PULLUP true
#define BTNS_ACTIVE_LOW false



void setupInput();
void loopInput();

void updateEncoder();
void updateButtons();

bool isPressedSat();
bool isPressedVal();
bool isPressedEnc();
// bool isButtonPressed(OneButtonTiny btn);

byte encoderValueAsByte();
int encoderValue();

#endif
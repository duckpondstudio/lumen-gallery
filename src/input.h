#ifndef INPUT_H
#define INPUT_H

#include <avr/io.h>

#include <Arduino.h>
#include <RotaryEncoder.h>

#include "pindef.h"
#include "button.h"
#include "leds.h"

#define BTNS_DEBOUNCE 35
#define BTNS_PULLUP false
#define BTNS_ACTIVE_LOW false



void setupInput();
void loopInput();

void updateEncoder();
void updateButtons();

bool isPressedSat();
bool isPressedVal();
bool isPressedEnc();

byte encoderValueAsByte();
int encoderValue();

#endif
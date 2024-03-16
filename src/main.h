#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#include "pindef.h"
#include "input.h"
#include "leds.h"
#include "savedata.h"

#define INITIAL_DELAY 250


void setupLEDs();
void loopLEDs();

#endif
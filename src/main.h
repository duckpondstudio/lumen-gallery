#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#include "input.h"
#include "leds.h"

#define INTERVAL_LOOP 1
#define INTERVAL_INPUT 1
#define INTERVAL_LEDS 1000


void setupLEDs();
void loopLEDs();

#endif
#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <FastLED.h>

#include "input.h"
#include "leds.h"

#define LOOP_INTERVAL 1

void setupLEDs();
void loopLEDs();

#endif
#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <FastLED.h>

#include "input.h"
#include "leds.h"

#define LOOP_INTERVAL 30


void setupLEDs();
void loopLEDs();

CRGB getColor();

#endif
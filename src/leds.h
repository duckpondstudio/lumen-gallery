#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include <FastLED.h>
#include "pindef.h"

void setupLEDs();
void loopLEDs();

CHSV getColorHSV();
CRGB getColorRGB();

#endif
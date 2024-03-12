#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include <FastLED.h>


void setupLEDs();
void loopLEDs(void *);

CHSV getColorHSV();
CRGB getColorRGB();

#endif
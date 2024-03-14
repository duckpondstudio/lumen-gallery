#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include <FastLED.h>
#include "pindef.h"

#define CHIPSET WS2812B
#define RGB_ORDER GRB
#define MAX_BRIGHTNESS 60

void setupLEDs();
void loopLEDs();
void updateLEDs();

void valueDelta(int delta);

CHSV getColorHSV();
CRGB getColorRGB();

#endif
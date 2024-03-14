#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include <FastLED.h>
#include "pindef.h"

#define CHIPSET WS2812B
#define RGB_ORDER GRB

#define LEDS_COUNT

#define H_DELTA_MULT 1
#define S_DELTA_MULT 4
#define V_DELTA_MULT 2

#define MIN_BRIGHTNESS 4
#define MAX_BRIGHTNESS 50

void setupLEDs();
void loopLEDs();
void updateLEDs();

void valueDelta(int delta);

CHSV getColorHSV();
CRGB getColorRGB();

#endif
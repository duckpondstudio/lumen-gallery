#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include <FastLED.h>
#include "pindef.h"

#define CHIPSET WS2812B
#define RGB_ORDER GRB

#define LEDS_COUNT 40

#define H_DELTA_MULT 2
#define S_DELTA_MULT 5
#define V_DELTA_MULT 2

#define MIN_BRIGHTNESS 5
#define MAX_BRIGHTNESS 100

void setupLEDs();
void loopLEDs();
void updateLEDs();

void valueDelta(int delta);

CHSV getColorHSV();
CRGB getColorRGB();

#endif
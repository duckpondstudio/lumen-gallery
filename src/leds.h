#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include <FastLED.h>

#include "pindef.h"
#include "ledarrays.h"
#include "input.h"
#include "savedata.h"

#define CHIPSET WS2812B
#define RGB_ORDER GRB

#define LEDS_COUNT 40

#define H_DELTA_MULT 2
#define S_DELTA_MULT 5
#define V_DELTA_MULT 2

#define MIN_BRIGHTNESS 5
#define MAX_BRIGHTNESS 150

void setupLEDs();
void loopLEDs();
void updateLEDs();

void loadLEDData();
void saveLEDData();

void doubleButtonPush(); 
void encoderPush();

void valueDelta(int delta);

void setCurrentColorH(byte value);
void setCurrentColorS(byte value);
void setCurrentColorV(byte value);
byte getCurrentColorH();
byte getCurrentColorS();
byte getCurrentColorV();

CHSV getCurrentColorHSV();
CRGB getCurrentColorRGB();
CHSV getColor1HSV();
CRGB getColor1RGB();
CHSV getColor2HSV();
CRGB getColor2RGB();

#endif
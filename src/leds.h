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

#define LEDS_COUNT 36 // number of LEDs

#define H_DELTA_MULT 2
#define S_DELTA_MULT 5
#define V_DELTA_MULT 2

#define MAIN_BRIGHTNESS 25 // base brightness to set FastLED to 

#define MIN_BRIGHTNESS 5 // min value of V in LED HSV calc 
#define MAX_BRIGHTNESS 150 // max value of V in LED HSV calc 


void setupLEDs();
void loopLEDs();
void updateLEDs(bool autoSave = true);

void loadLEDData();
void saveLEDData();
void clearLEDLocalData();

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

// inline assignment for a debug light (first LED in the strip turns on to assigned debug colour)
void setDebugLight(bool enabled);
// convenience getter for current state of the debug light 
bool getDebugLight();

#endif
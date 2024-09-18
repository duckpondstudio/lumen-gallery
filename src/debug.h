#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include <FastLED.h>

#include "pindef.h"
#include "leds.h"

#define DEBUG_ENABLED true // use debug systems / tools
#define DEBUG_ONLY true    // in main.h, if DEBUG_ENABLED, exclude setup and loop for non-debug functions

#define DEBUG_LED_CHIPSET WS2812B // chipset to use for debugging. Also see CHIPSET in leds.h
#define DEBUG_LED_RGB_ORDER GRB   // RGB ordering to use for debugging. Also see RGB_ORDER in leds.h

// for debugging multiple LED pins with diff colours.
// 1 = pins0/1/2/3,
// 2 = 4/5/6/7,
// 3 = 8/9/10/0,
// 4 = 3/7/2/8,
// 0/else = none
#define DEBUG_MULTI_PINS_SET 0
#define DEBUG_MULTI_BLINK_CYCLE false // cycle thru DEBUG_MULTI_PINS_SET with numbered blinks

#define DEBUG_SINGLE_LED true   // display a single LED
#define DEBUG_BLINK_LED false   // blink a single LED
#define DEBUG_LED_DATA_PIN 7    // data pin to use for a single LED
#define DEBUG_LEDS_TEST_COUNT 3 // how many LEDs on the strip to test (default 1)

#define DEBUG_HILOW_OUT true
#define DEBUG_HILOW_PIN 5

void setupDebug();
void loopDebug();

void cycleBlinkLEDs();
void clearLEDs();
CRGB *getBlinkCycleLEDs();
bool debugMultiPinsValid();

#endif
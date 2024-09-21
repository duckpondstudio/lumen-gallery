#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include <FastLED.h>

#include "main.h"
#include "pindef.h"
#include "leds.h"

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

#define DEBUG_BASIC_LED true     // display a single LED
#define DEBUG_BLINK_LED false    // blink a single LED
#define DEBUG_LED_DATA_PIN 7     // data pin to use for a single LED
#define DEBUG_LEDS_TEST_COUNT 38 // how many LEDs on the strip to test (default 1)
#define DEBUG_LEDS_RAINBOW true  // if true, assigns all LEDs on the strip through HSV 0-255
#define DEBUG_RAINBOW_CYCLE true // if true, and if debugging rainbow, makes the rainbow animate

#define DEBUG_LED_BRIGHTNESS 25 // if >= 0 && < 256, sets debug LED brightness to this value on setup

#define DEBUG_HILOW_OUT true
#define DEBUG_HILOW_PIN 5

void setupDebug();
void loopDebug();

void cycleBlinkLEDs();
void clearLEDs();
CRGB *getBlinkCycleLEDs();
bool debugMultiPinsValid();
CHSV getRainbowColor(int current, int max, int offset = 0);

#endif
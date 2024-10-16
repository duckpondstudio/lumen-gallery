#ifndef DEBUG_H

// Note: Defs beginning with DEBUG_D_ are used internally in the debugging system, specifically debug.h and debug.cpp.
//       Defs that are simply DEBUG_ and then the description of the definition, are used throughout the codebase.
#define DEBUG_H

#include <Arduino.h>
#include <FastLED.h>

#include "main.h"
#include "pindef.h"
#include "leds.h"

// -------------------------------------------------
// ---------------                   ---------------
// --------------- DEBUG DEFINITIONS ---------------
// ---------------                   ---------------
// -------------------------------------------------
//
// ------- INTERNAL DEBUG SYSTEM DEFINITIONS -------
// -------  that begin with DEBUG_D_[name]   -------

#define DEBUG_D_LED_CHIPSET WS2812B // chipset to use for debugging. Also see CHIPSET in leds.h
#define DEBUG_D_LED_RGB_ORDER GRB   // RGB ordering to use for debugging. Also see RGB_ORDER in leds.h

// for debugging multiple LED pins with diff colours.
// 1 = pins0/1/2/3,
// 2 = 4/5/6/7,
// 3 = 8/9/10/0,
// 4 = 3/7/2/8,
// 0/else = none
#define DEBUG_D_MULTI_PINS_SET 0
#define DEBUG_D_MULTI_BLINK_CYCLE false // cycle thru DEBUG_MULTI_PINS_SET with numbered blinks

#define DEBUG_D_BASIC_LED true     // display a single LED
#define DEBUG_D_BLINK_LED false    // blink a single LED
#define DEBUG_D_LED_DATA_PIN 7     // data pin to use for a single LED
#define DEBUG_D_LEDS_TEST_COUNT 38 // how many LEDs on the strip to test (default 1)
#define DEBUG_D_LEDS_RAINBOW true  // if true, assigns all LEDs on the strip through HSV 0-255
#define DEBUG_D_RAINBOW_CYCLE true // if true, and if debugging rainbow, makes the rainbow animate

#define DEBUG_D_FLED_BRIGHTNESS 25      // if >= 0 && < 256, sets debug LED brightness to this value on setup
#define DEBUG_D_FLED_SET_MAX_POWER true // if true, limit FastLED to drawing the max specified voltage/current
#define DEBUG_D_FLED_MAX_VOLTAGE 5      // max voltage FastLED will draw, in V
#define DEBUG_D_FLED_MAX_CURRENT 1000   // max current FastLED will draw, in mA

#define DEBUG_D_HILOW_OUT false // basic debug tool that toggles the hilow pin HIGH/LOW on 1s intervals, for LED and IO debugging
#define DEBUG_D_HILOW_PIN 5     // pin to toggle if DEBUG_D_HILOW_OUT is true

//
// ------- EXTERNAL DEBUG SYSTEM DEFINITIONS -------
// -------  beginning just with DEBUG_[name] -------
//

#define DEBUG_LED_DEBUGLIGHT_ENABLED true    // allow use of the DebugLight in leds.cpp (toggleable first LED in the strip)
#define DEBUG_LED_DEBUGLIGHT_BTN_TOGGLE true // ifi DebugLight is enabled, allows toggling via Sat/Val/Enc buttons

//
// ------- METHOD AND PROPERTY DECLARATION -------
//

void setupDebug();
void loopDebug();

void cycleBlinkLEDs();
void clearLEDs();
CRGB *getBlinkCycleLEDs();
bool debugMultiPinsValid();
CHSV getRainbowColor(int current, int max, int offset = 0);

#endif
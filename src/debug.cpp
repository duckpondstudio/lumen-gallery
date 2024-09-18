#include "debug.h"

CRGB debugLEDs[1];

CRGB debugLEDsA[1];
CRGB debugLEDsB[1];
CRGB debugLEDsC[1];
CRGB debugLEDsD[1];
CRGB debugLEDsE[1];

CRGB debugAllLEDs0[1];

int second = 0;

bool blink = false;

void setupDebug()
{
    if (!DEBUG_ENABLED)
        return;

    if (DEBUG_MULTIPLE_PINS_SET > 0 || DEBUG_MULTIPLE_PINS_SET <= 4)
    {
        // setup multiple pins
        switch (DEBUG_MULTIPLE_PINS_SET)
        {
        case 1:
            // 0/1/2/3
            FastLED.addLeds<DEBUG_LED_CHIPSET, 0, DEBUG_LED_RGB_ORDER>(debugLEDsA, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 1, DEBUG_LED_RGB_ORDER>(debugLEDsB, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 2, DEBUG_LED_RGB_ORDER>(debugLEDsC, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 3, DEBUG_LED_RGB_ORDER>(debugLEDsD, 1);
            break;
        case 2:
            // 4/5/6/7
            FastLED.addLeds<DEBUG_LED_CHIPSET, 4, DEBUG_LED_RGB_ORDER>(debugLEDsA, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 5, DEBUG_LED_RGB_ORDER>(debugLEDsB, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 6, DEBUG_LED_RGB_ORDER>(debugLEDsC, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 7, DEBUG_LED_RGB_ORDER>(debugLEDsD, 1);
            break;
        case 3:
            // 8/9/10/0
            FastLED.addLeds<DEBUG_LED_CHIPSET, 8, DEBUG_LED_RGB_ORDER>(debugLEDsA, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 9, DEBUG_LED_RGB_ORDER>(debugLEDsB, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 10, DEBUG_LED_RGB_ORDER>(debugLEDsC, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 0, DEBUG_LED_RGB_ORDER>(debugLEDsD, 1);
            break;
        case 4:
            FastLED.addLeds<DEBUG_LED_CHIPSET, 3, DEBUG_LED_RGB_ORDER>(debugLEDsA, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 7, DEBUG_LED_RGB_ORDER>(debugLEDsB, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 2, DEBUG_LED_RGB_ORDER>(debugLEDsC, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 8, DEBUG_LED_RGB_ORDER>(debugLEDsD, 1);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 6, DEBUG_LED_RGB_ORDER>(debugLEDsE, 1);
            debugLEDsE[0] = CRGB::Magenta;
            break;
        }
        debugLEDsA[0] = CRGB::Red;
        debugLEDsB[0] = CRGB::Green;
        debugLEDsC[0] = CRGB::Blue;
        debugLEDsD[0] = CRGB::White;
        FastLED.show();
    }

    if (DEBUG_SINGLE_LED || DEBUG_BLINK_LED)
    {
        // debug a single LED for display or blinking
        FastLED.addLeds<DEBUG_LED_CHIPSET, PIN_LEDS, DEBUG_LED_RGB_ORDER>(debugLEDs, 1);
        if (DEBUG_BLINK_LED)
            blink = true;
        debugLEDs[0] = CRGB::White;
        FastLED.show();
    }
}

void loopDebug()
{
    if (!DEBUG_ENABLED)
        return;

    if (DEBUG_BLINK_LED)
    {

        bool oneSecondTick = false;
        second++;
        if (second >= 1000)
        {
            second = 0;
            oneSecondTick = true;
        }
        if (oneSecondTick)
        {
            blink = !blink;
            debugLEDs[0] = blink ? CRGB::White : CRGB::Black;
            FastLED.show();
        }
    }
}
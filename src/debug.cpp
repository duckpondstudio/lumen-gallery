#include "debug.h"

CRGB debugLEDs[1];

CRGB debugLEDsA[1];
CRGB debugLEDsB[1];
CRGB debugLEDsC[1];
CRGB debugLEDsD[1];

CRGB debugAllLEDs0[1];

int second = 0;          // one second timer used for blink
int cycleDelay = 0;      // delay in ms for cycle logic flow
int cycleStep = 0;       // current step in cycle logic flow
int cycleTarget = 1;     // target for which debugLEDs array to return
int cycleIterations = 0; // counter for num times cycle to blink

bool blinkOn = false; // for basic blink, is LED currently ON or OFF

void setupDebug()
{
    if (!DEBUG_ENABLED)
        return;

    if (debugMultiPinsValid())
    {
        // setup multiple pins
        switch (DEBUG_MULTI_PINS_SET)
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
            break;
        }
        if (!DEBUG_MULTI_BLINK_CYCLE)
        {
            debugLEDsA[0] = CRGB::Red;
            debugLEDsB[0] = CRGB::Green;
            debugLEDsC[0] = CRGB::Blue;
            debugLEDsD[0] = CRGB::Magenta;
            FastLED.show();
        }
    }

    if (DEBUG_SINGLE_LED || DEBUG_BLINK_LED)
    {
        // debug a single LED for display or blinking
        FastLED.addLeds<DEBUG_LED_CHIPSET, PIN_LEDS, DEBUG_LED_RGB_ORDER>(debugLEDs, 1);
        if (DEBUG_BLINK_LED)
            blinkOn = true;
        debugLEDs[0] = CRGB::White;
        FastLED.show();
    }
}

void loopDebug()
{
    if (!DEBUG_ENABLED)
        return;

    if (DEBUG_MULTI_BLINK_CYCLE && debugMultiPinsValid())
    {
        cycleBlinkLEDs();
    }

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
            blinkOn = !blinkOn;
            debugLEDs[0] = blinkOn ? CRGB::White : CRGB::Black;
            FastLED.show();
        }
    }
}

void cycleBlinkLEDs()
{
    int color = CRGB::White;

    if (cycleDelay > 0)
    {
        cycleDelay--;
        return;
    }

    switch (cycleStep)
    {
    case 1:
        // clear LEDs and wait
        cycleStep++;
        clearLEDs();
        cycleDelay = 500;
        break;
    case 2:
        // turn on for one second
        getBlinkCycleLEDs()[0] = color;
        FastLED.show();
        cycleDelay = 1000;
        cycleIterations = cycleTarget; // set iteration count
        cycleStep++;
        break;
    case 3:
        // blink off
        getBlinkCycleLEDs()[0] = CRGB::Black;
        FastLED.show();
        cycleDelay = 250;
        cycleStep++;
        break;
    case 4:
        // blink on
        getBlinkCycleLEDs()[0] = color;
        FastLED.show();
        cycleDelay = 250;
        cycleIterations--; // decrement iteration count
        if (cycleIterations > 0)
        {
            cycleStep--; // iterations are remaining, return to step 2
        }
        else
        {
            // iterations complete, blink off move to next pin
            getBlinkCycleLEDs()[0] = CRGB::Black;
            FastLED.show();
            cycleTarget++;
            if (cycleTarget > 4)
            {
                cycleTarget = 1;
            }
            cycleStep = 1;
        }
        break;
    }
}
CRGB *getBlinkCycleLEDs()
{
    switch (cycleTarget)
    {
    case 1:
        return debugLEDsA;
    case 2:
        return debugLEDsB;
    case 3:
        return debugLEDsC;
    case 4:
        return debugLEDsD;
    }
    return debugLEDs;
}
void clearLEDs()
{
    debugLEDs[0] = CRGB::Black;
    debugLEDsA[0] = CRGB::Black;
    debugLEDsB[0] = CRGB::Black;
    debugLEDsC[0] = CRGB::Black;
    debugLEDsD[0] = CRGB::Black;
    FastLED.show();
}

bool debugMultiPinsValid()
{
    return DEBUG_MULTI_PINS_SET > 0 && DEBUG_MULTI_PINS_SET <= 4;
}
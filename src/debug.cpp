#include "debug.h"

CRGB debugLEDs[DEBUG_LEDS_TEST_COUNT];

CRGB debugLEDsA[DEBUG_LEDS_TEST_COUNT];
CRGB debugLEDsB[DEBUG_LEDS_TEST_COUNT];
CRGB debugLEDsC[DEBUG_LEDS_TEST_COUNT];
CRGB debugLEDsD[DEBUG_LEDS_TEST_COUNT];

CRGB debugAllLEDs0[DEBUG_LEDS_TEST_COUNT];

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
            FastLED.addLeds<DEBUG_LED_CHIPSET, 0, DEBUG_LED_RGB_ORDER>(debugLEDsA, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 1, DEBUG_LED_RGB_ORDER>(debugLEDsB, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 2, DEBUG_LED_RGB_ORDER>(debugLEDsC, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 3, DEBUG_LED_RGB_ORDER>(debugLEDsD, DEBUG_LEDS_TEST_COUNT);
            break;
        case 2:
            // 4/5/6/7
            FastLED.addLeds<DEBUG_LED_CHIPSET, 4, DEBUG_LED_RGB_ORDER>(debugLEDsA, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 5, DEBUG_LED_RGB_ORDER>(debugLEDsB, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 6, DEBUG_LED_RGB_ORDER>(debugLEDsC, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 7, DEBUG_LED_RGB_ORDER>(debugLEDsD, DEBUG_LEDS_TEST_COUNT);
            break;
        case 3:
            // 8/9/10/0
            FastLED.addLeds<DEBUG_LED_CHIPSET, 8, DEBUG_LED_RGB_ORDER>(debugLEDsA, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 9, DEBUG_LED_RGB_ORDER>(debugLEDsB, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 10, DEBUG_LED_RGB_ORDER>(debugLEDsC, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 0, DEBUG_LED_RGB_ORDER>(debugLEDsD, DEBUG_LEDS_TEST_COUNT);
            break;
        case 4:
            // 3/7/2/8
            FastLED.addLeds<DEBUG_LED_CHIPSET, 3, DEBUG_LED_RGB_ORDER>(debugLEDsA, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 7, DEBUG_LED_RGB_ORDER>(debugLEDsB, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 2, DEBUG_LED_RGB_ORDER>(debugLEDsC, DEBUG_LEDS_TEST_COUNT);
            FastLED.addLeds<DEBUG_LED_CHIPSET, 8, DEBUG_LED_RGB_ORDER>(debugLEDsD, DEBUG_LEDS_TEST_COUNT);
            break;
        }
        if (!DEBUG_MULTI_BLINK_CYCLE)
        {
            for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
            {
                debugLEDsA[i] = CRGB::Red;
                debugLEDsB[i] = CRGB::Green;
                debugLEDsC[i] = CRGB::Blue;
                debugLEDsD[i] = CRGB::Magenta;
            }
            FastLED.show();
        }
    }

    if (DEBUG_SINGLE_LED || DEBUG_BLINK_LED)
    {
        // debug a single LED for display or blinking
        FastLED.addLeds<DEBUG_LED_CHIPSET, DEBUG_LED_DATA_PIN, DEBUG_LED_RGB_ORDER>(debugLEDs, 1);
        if (DEBUG_BLINK_LED)
            blinkOn = true;
        for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
        {
            debugLEDs[i] = CRGB::Cyan;
        }
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
            for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
            {
                debugLEDs[0] = blinkOn ? CRGB::Cyan : CRGB::Black;
            }
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
        for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
        {
            getBlinkCycleLEDs()[i] = color;
        }
        FastLED.show();
        cycleDelay = 1000;
        cycleIterations = cycleTarget; // set iteration count
        cycleStep++;
        break;
    case 3:
        // blink off
        for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
        {
            getBlinkCycleLEDs()[i] = CRGB::Black;
        }
        FastLED.show();
        cycleDelay = 250;
        cycleStep++;
        break;
    case 4:
        // blink on
        for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
        {
            getBlinkCycleLEDs()[i] = color;
        }
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
            for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
            {
                getBlinkCycleLEDs()[i] = CRGB::Black;
            }
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
    for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
    {
        debugLEDs[i] = CRGB::Black;
        debugLEDsA[i] = CRGB::Black;
        debugLEDsB[i] = CRGB::Black;
        debugLEDsC[i] = CRGB::Black;
        debugLEDsD[i] = CRGB::Black;
    }
    FastLED.show();
}

bool debugMultiPinsValid()
{
    return DEBUG_MULTI_PINS_SET > 0 && DEBUG_MULTI_PINS_SET <= 4;
}
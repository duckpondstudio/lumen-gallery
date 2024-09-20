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

int rainbowOffset = 0;
int rainbowTimer = 0;
int rainbowInterval = 20;

bool blinkOn = false; // for basic blink, is LED currently ON or OFF
bool hiLow = false;   // is hilow output high (t) or low (f)

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

        // set brightness 
        if (DEBUG_LED_BRIGHTNESS >= 0 && DEBUG_LED_BRIGHTNESS < 256) {
            FastLED.setBrightness(DEBUG_LED_BRIGHTNESS);
        }

        // clear buffer + push to strip (fixes lingering bugs in data line)
        FastLED.clearData();
        FastLED.show();

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

    // may interfere with multipins valid test 
    if (DEBUG_BASIC_LED || DEBUG_BLINK_LED || DEBUG_LEDS_RAINBOW)
    {
        // debug a single LED for display or blinking
        FastLED.addLeds<DEBUG_LED_CHIPSET, DEBUG_LED_DATA_PIN, DEBUG_LED_RGB_ORDER>(debugLEDs, DEBUG_LEDS_TEST_COUNT);

        // set brightness 
        if (DEBUG_LED_BRIGHTNESS >= 0 && DEBUG_LED_BRIGHTNESS < 256) {
            FastLED.setBrightness(DEBUG_LED_BRIGHTNESS);
        }

        if (DEBUG_BLINK_LED)
            blinkOn = true;

        for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
        {
            if (DEBUG_LEDS_RAINBOW && DEBUG_LEDS_TEST_COUNT > 1)
            {
                debugLEDs[i] = getRainbowColor(i, DEBUG_LEDS_TEST_COUNT);
            }
            else
            {
                debugLEDs[i] = CRGB::Cyan;
            }
        }

        // clear buffer + push to strip (fixes lingering bugs in data line)
        FastLED.clear(true);

        FastLED.show();
    }

    if (DEBUG_HILOW_OUT)
    {
        pinMode(DEBUG_HILOW_PIN, OUTPUT);
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

    bool oneSecondTick = false; // track the 1s timer
    if (DEBUG_BLINK_LED || DEBUG_HILOW_OUT)
    {

        second++;
        if (second >= 1000)
        {
            second = 0;
            oneSecondTick = true;
        }
        if (oneSecondTick)
        {
            if (DEBUG_HILOW_OUT)
            {
                hiLow = !hiLow;
                digitalWrite(DEBUG_HILOW_PIN, hiLow ? HIGH : LOW);
            }

            if (DEBUG_BLINK_LED)
            {
                blinkOn = !blinkOn;
                // if cycling rainbow LEDs, that code will actually turn the LEDs on / off
                if (!(DEBUG_LEDS_RAINBOW && DEBUG_RAINBOW_CYCLE))
                    for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
                    {
                        {
                            debugLEDs[0] = blinkOn ? CRGB::Cyan : CRGB::Black;
                        }
                        FastLED.show();
                    }
            }
            else
            {
                // do not use 1s tick beyond here unless blinking
                oneSecondTick = false;
            }
        }
    }

    if (DEBUG_LEDS_RAINBOW && DEBUG_RAINBOW_CYCLE)
    {
        rainbowTimer++;
        bool incrementingRainbowTimer = rainbowTimer >= rainbowInterval;
        // either the rainbow timer has incremented, or a blink tick has passed
        if (incrementingRainbowTimer || oneSecondTick)
        {
            if (incrementingRainbowTimer)
            {
                rainbowOffset++;
                if (rainbowOffset > 255)
                {
                    rainbowOffset = 0;
                }
                rainbowTimer = 0;
            }
            for (int i = 0; i < DEBUG_LEDS_TEST_COUNT; i++)
            {
                if (DEBUG_BLINK_LED)
                {
                    if (blinkOn)
                        debugLEDs[i] = getRainbowColor(i, DEBUG_LEDS_TEST_COUNT, rainbowOffset);
                    else
                        debugLEDs[i] = CRGB::Black;
                }
                else
                {
                    debugLEDs[i] = getRainbowColor(i, DEBUG_LEDS_TEST_COUNT, rainbowOffset);
                }
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

CHSV getRainbowColor(int current, int max, int offset = 0)
{
    int value = (constrain(current, 0, 255) + offset) % 255;
    return CHSV(value, 255, 255);
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
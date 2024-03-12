#include "leds.h"
#include "input.h"

CRGB leds[40];

void setupLEDs()
{
    FastLED.setBrightness(100);
    FastLED.addLeds<WS2812B, 5, GRB>(leds, 40);
}

void loopLEDs()
{

    for (int i = 0; i < 40; i++)
    {
        leds[i] = getColor();
    }
    FastLED.show();
}

CRGB getColor()
{
    if (isPressedSat())
    {
        if (isPressedVal())
        {
            return CRGB::White;
        }
        return CRGB::Green;
    }
    else if (isPressedVal())
    {
        return CRGB::Blue;
    }
    return CRGB::Red;
}
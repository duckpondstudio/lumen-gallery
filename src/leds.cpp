#include "leds.h"
#include "input.h"

CRGB leds[40];

byte hsv = 0;

void setupLEDs()
{
    FastLED.setBrightness(100);
    FastLED.addLeds<WS2812B, 5, GRB>(leds, 40);
}

void loopLEDs()
{
    for (int i = 0; i < 40; i++)
    {
        leds[i] = getColorRGB();
    }

    FastLED.show();
}

CRGB getColorRGB() {
    return CRGB(getColorHSV());
}
CHSV getColorHSV()
{
    if (isPressedSat())
    {
        if (isPressedVal())
        {
            return CHSV(0, 0, 255);
        }
        return CHSV(96, 255, 255);
    }
    else if (isPressedVal())
    {
        return CHSV(160, 255, 255);
    }
    return CHSV(0, 255, 255);
}
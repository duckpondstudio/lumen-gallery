#include "leds.h"
#include "input.h"

CRGB leds[40];

byte hsv = 0;

void setupLEDs()
{
    FastLED.setBrightness(100);
    FastLED.addLeds<WS2812, 5, GRB>(leds, 40);
}

byte test = 0;

void loopLEDs()
{

    CRGB color = CRGB::Green;
    // if (isPressedEnc())
    // {
    //     test = 1;
    // }
    // if (test > 0)
    // {
    //     test--;
    //     color = CRGB::Blue;
    // }

        for (int i = 0; i < 40; i++)
        {
            // leds[i] = CRGB::Blue;
            leds[i] = color;
            // leds[i] = CRGB(getColorHSV());
        }

        FastLED.show();
}

CHSV getColorHSV()
{
    // if (isPressedSat())
    // {
    //     if (isPressedVal())
    //     {
    //         return CHSV(0, 0, 255);
    //     }
    //     return CHSV(96, 255, 255);
    // }
    // else if (isPressedVal())
    // {
    //     return CHSV(0, 255, 255);
    // }
    return CHSV(160, 255, 255);
}
CRGB getColorRGB()
{
    return CRGB(getColorHSV());
}
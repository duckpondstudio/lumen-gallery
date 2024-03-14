#include "leds.h"
#include "input.h"

CRGB leds[40];

byte hsv = 0;

void setupLEDs()
{
    FastLED.setBrightness(100);
    FastLED.addLeds<WS2812, PIN_LEDS, GRB>(leds, 40);
}

byte test = 0;

void loopLEDs()
{

    CRGB color = CRGB(getColorHSV());

    bool temp = false;
    CRGB c = CRGB::Black;

    if (isPressedVal()) {
        temp = true;
        c.red = 255;
    }
    if (isPressedSat()) {
        temp = true;
        c.green = 255;
    }
    if (isPressedEnc()) {
        temp = true;
        c.blue = 255;
    }
    
    if (temp) {
        color = c;
    }

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
    return CHSV(encoderValueAsByte(), 255, 255);
}
CRGB getColorRGB()
{
    return CRGB(getColorHSV());
}
#include "leds.h"
#include "input.h"

CRGB leds[40];

byte color1H = 0;
byte color1S = 255;
byte color1V = 255;

void setupLEDs()
{
    FastLED.setBrightness(100);
    FastLED.addLeds<CHIPSET, PIN_LEDS, RGB_ORDER>(leds, MAX_BRIGHTNESS);
}

byte test = 0;

void loopLEDs()
{

    CRGB color = CRGB(getColorHSV());

    for (int i = 0; i < 40; i++)
    {
        leds[i] = color;
    }

    FastLED.show();
}

CHSV getColorHSV()
{
    return CHSV(color1H, color1S, color1V);
}
CRGB getColorRGB()
{
    return CRGB(getColorHSV());
}
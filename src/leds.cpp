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

    updateLEDs();
}

byte test = 0;

void loopLEDs()
{
}

void updateLEDs()
{

    // determine HSV

    bool sat = isPressedSat();
    bool val = isPressedVal();

    // apply colors

    // color1H = encoderValueAsByte();

    CRGB color = CRGB(getColorHSV());

    for (int i = 0; i < 40; i++)
    {
        leds[i] = color;
    }

    FastLED.show();
}

// a value delta (typically +/- some small number) has been received from the encoder
void valueDelta(int delta)
{

    // determine state
    if (isPressedSat())
    {
        // saturation
        if (isPressedVal())
        {
            // sat + val - neither
        }
        else
        {
            // saturation
            color1S += delta;
        }
    }
    else if (isPressedVal())
    {
        // value
        color1V += delta;
    }
    else
    {
        // hue
        color1H += delta;
    }

    updateLEDs();
}

CHSV getColorHSV()
{
    return CHSV(color1H, color1S, color1V);
}
CRGB getColorRGB()
{
    return CRGB(getColorHSV());
}
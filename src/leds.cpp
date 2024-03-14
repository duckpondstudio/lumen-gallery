#include "leds.h"
#include "input.h"

CRGB leds[LEDS_COUNT];

byte color1H = 0;
byte color1S = 255;
byte color1V = 255;

void setupLEDs()
{
    FastLED.setBrightness(100);
    FastLED.addLeds<CHIPSET, PIN_LEDS, RGB_ORDER>(leds, LEDS_COUNT);

    updateLEDs();
}

byte test = 0;

void loopLEDs()
{
}

void updateLEDs()
{

    // apply colors
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
            color1S += delta * S_DELTA_MULT;
        }
    }
    else if (isPressedVal())
    {
        // value
        color1V += delta * V_DELTA_MULT;
    }
    else
    {
        // hue
        color1H += delta * H_DELTA_MULT;
    }

    updateLEDs();
}

CHSV getColorHSV()
{
    return CHSV(color1H, color1S, map(color1V, 0, 255, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
}
CRGB getColorRGB()
{
    return CRGB(getColorHSV());
}
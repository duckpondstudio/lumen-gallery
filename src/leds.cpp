#include "leds.h"
#include "input.h"

CRGB leds[LEDS_COUNT];

byte color1H = 0;
byte color1S = 255;
byte color1V = 255;

void setupLEDs()
{
    // FastLED.setBrightness(100);
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
            int targetH = color1H + (delta * V_DELTA_MULT);
            color1H = (byte)targetH % 255;
        }
        else
        {
            // saturation
            int targetS = color1S + (delta * S_DELTA_MULT);
            if (targetS > 255)
            {
                targetS = 255;
            }
            else if (targetS < 0)
            {
                targetS = 0;
            }
            color1S = (byte)targetS;
        }
    }
    else if (isPressedVal())
    {
        // value
        int targetV = color1V + (delta * V_DELTA_MULT);
        if (targetV > 255)
        {
            targetV = 255;
        }
        else if (targetV < 0)
        {
            targetV = 0;
        }
        color1V = (byte)map(targetV, 0, 255, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
    }
    else
    {
        // hue
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
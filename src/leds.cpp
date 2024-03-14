#include "leds.h"
#include "input.h"

CRGB leds[LEDS_COUNT];

byte color1H = 0;
byte color1S = 255;
byte color1V = MAX_BRIGHTNESS;

byte color2H = 0;
byte color2S = 255;
byte color2V = MAX_BRIGHTNESS;

int currentColor = 1;

void setupLEDs()
{
    // FastLED.setBrightness(100);
    FastLED.addLeds<CHIPSET, PIN_LEDS, RGB_ORDER>(leds, LEDS_COUNT);

    updateLEDs();
}

byte test = 0;

void loopLEDs()
{
    // leds[0] = isPressedVal() ? CRGB::Blue : CRGB::Red;
    // leds[1] = isPressedSat() ? CRGB::Blue : CRGB::Red;
    // leds[2] = isPressedEnc() ? CRGB::Blue : CRGB::Red;
    // FastLED.show();
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
        if (targetV > MAX_BRIGHTNESS)
        {
            targetV = MAX_BRIGHTNESS;
        }
        else if (targetV < MIN_BRIGHTNESS)
        {
            targetV = MIN_BRIGHTNESS;
        }
        color1V = (byte)targetV;
    }
    else
    {
        // hue
        int targetH = color1H + (delta * H_DELTA_MULT);
        color1H = (byte)targetH % 255;
    }

    updateLEDs();
}

CHSV getColorHSV()
{
    return CHSV(color1H, color1S,
                color1V == MIN_BRIGHTNESS ? 0 : color1V);
    // if value is zero, color is off
}
CRGB getColorRGB()
{
    return CRGB(getColorHSV());
}
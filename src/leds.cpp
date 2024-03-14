#include "leds.h"
#include "input.h"

CRGB leds[LEDS_COUNT];

byte color1H = 0;
byte color1S = 255;
byte color1V = MAX_BRIGHTNESS;

byte color2H = 127;
byte color2S = 255;
byte color2V = MAX_BRIGHTNESS;

bool currentColor2 = false;

static bool lastPressedEnc = false;

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

    bool pressedEnc = isPressedEnc();
    if (pressedEnc != lastPressedEnc)
    {
        lastPressedEnc = pressedEnc;
        if (pressedEnc)
        {
            // pressed encoder down, switch colors
            currentColor2 = !currentColor2;
            updateLEDs();
        }
    }
}

void updateLEDs()
{

    // apply colors
    CRGB color = getColorRGB();

    if (isPressedSat() && isPressedVal()) {
        color = CRGB::Red;
    }

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
            int targetS = getCurrentColorS() + (delta * S_DELTA_MULT);
            if (targetS > 255)
            {
                targetS = 255;
            }
            else if (targetS < 0)
            {
                targetS = 0;
            }
            setCurrentColorS((byte)targetS);
        }
    }
    else if (isPressedVal())
    {
        // value
        int targetV = getCurrentColorV() + (delta * V_DELTA_MULT);
        if (targetV > MAX_BRIGHTNESS)
        {
            targetV = MAX_BRIGHTNESS;
        }
        else if (targetV < MIN_BRIGHTNESS)
        {
            targetV = MIN_BRIGHTNESS;
        }
        setCurrentColorV((byte)targetV);
    }
    else
    {
        // hue
        int targetH = getCurrentColorH() + (delta * H_DELTA_MULT);
        setCurrentColorH((byte)targetH);
    }

    updateLEDs();
}

void setCurrentColorH(byte value) { currentColor2 ? color2H = value : color1H = value; }
void setCurrentColorS(byte value) { currentColor2 ? color2S = value : color1S = value; }
void setCurrentColorV(byte value) { currentColor2 ? color2V = value : color1V = value; }
byte getCurrentColorH() { return currentColor2 ? color2H : color1H; }
byte getCurrentColorS() { return currentColor2 ? color2S : color1S; }
byte getCurrentColorV() { return currentColor2 ? color2V : color1V; }

CHSV getColorHSV()
{
    byte v = getCurrentColorV();
    return CHSV(getCurrentColorH(), getCurrentColorS(),
                v == MIN_BRIGHTNESS ? 0 : v);
    // if value is zero, color is off
}
CRGB getColorRGB()
{
    return CRGB(getColorHSV());
}
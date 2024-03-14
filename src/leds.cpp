#include "leds.h"
#include "input.h"

CRGB leds[LEDS_COUNT];

static byte color1H = 0;
static byte color1S = 255;
static byte color1V = MAX_BRIGHTNESS;

static byte color2H = 127;
static byte color2S = 255;
static byte color2V = MAX_BRIGHTNESS;

bool currentColor2 = false;

static int currentPattern = PATTERN_CT_MIN;
static bool lastToggledPattern = false;

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

    // determine toggle pattern state 
    if (lastToggledPattern) {
        // toggle pattern active, only disable on both inputs release 
        if (!isPressedSat() && !isPressedVal()) {
            lastToggledPattern = false;
        }
    } else {
        // toggle pattern inactive, look for both sat+val inputs 
        if (isPressedSat() && isPressedVal()) {
            // todo: integrate timer delay
            lastToggledPattern = true;
            currentPattern++;
            if (currentPattern > PATTERN_CT_MAX) {
                currentPattern = PATTERN_CT_MIN;
            }
            updateLEDs();
        }
    }

    // determine encoder state 
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
    CRGB color1 = getColor1RGB();
    CRGB color2 = getColor2RGB();

    if (isPressedSat() && isPressedVal()) {
        color1 = CRGB::Red;
        color2 = CRGB::Blue;
    }

    for (int i = 0; i < 40; i++)
    {
        // get blend value
        byte blendAmt = getLEDValue(currentPattern, i);

        CRGB blendColor = CRGB(
            blend8(color1.r, color2.r, blendAmt),
            blend8(color1.g, color2.g, blendAmt),
            blend8(color1.g, color2.b, blendAmt)
        );

        leds[i] = blendColor;
    }

    FastLED.show();
}

// a value delta (typically +/- some small number) has been received from the encoder
void valueDelta(int delta)
{

    // determine state
    if (!lastToggledPattern && isPressedSat())
    {
        // saturation (if toggle pattern state, only edit hue)
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
    else if (!lastToggledPattern && isPressedVal())
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

CHSV getCurrentColorHSV()
{
    return currentColor2 ? getColor2HSV() : getColor1HSV();
}
CRGB getCurrentColorRGB()
{
    return currentColor2 ? getColor2RGB() : getColor1RGB();
}
CHSV getColor1HSV()
{
    byte v = color1V;
    return CHSV(color1H, color1S,
                v == MIN_BRIGHTNESS ? 0 : v);
    // if value is zero, color is off
}
CRGB getColor1RGB()
{
    return CRGB(getColor1HSV());
}
CHSV getColor2HSV()
{
    byte v = color2V;
    return CHSV(color2H, color2S,
                v == MIN_BRIGHTNESS ? 0 : v);
    // if value is zero, color is off
}
CRGB getColor2RGB()
{
    return CRGB(getColor2HSV());
}
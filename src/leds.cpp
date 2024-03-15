#include "leds.h"

CRGB leds[LEDS_COUNT];

static byte color1H = 0;
static byte color1S = 255;
static byte color1V = MAX_BRIGHTNESS;

static byte color2H = 160;
static byte color2S = 255;
static byte color2V = MAX_BRIGHTNESS;

bool currentColor2 = false;

static int currentPattern = PATTERN_CT_DEFAULT;
static bool lastToggledPattern = false;
static bool patternInverted = false;

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

    // determine toggle pattern state
    if (lastToggledPattern)
    {
        // toggle pattern active, only disable on both inputs release
        if (!isPressedSat() || !isPressedVal())
        {
            lastToggledPattern = false;
        }
    }
    else
    {
        // toggle pattern inactive, look for both sat+val inputs
        if (isPressedSat() && isPressedVal())
        {
            // todo: integrate timer delay
            lastToggledPattern = true;
            currentPattern++;
            if (currentPattern > PATTERN_CT_MAX)
            {
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
            patternInverted = !patternInverted;
            updateLEDs();
        }
    }
}

void updateLEDs()
{

    // apply colors
    CRGB color1 = getColor1RGB();
    CRGB color2 = getColor2RGB();

    for (int i = 0; i < LEDS_COUNT; i++)
    {
        // get blend value
        byte blendAmt = getLEDValue(currentPattern, i);
        leds[i] = patternInverted ? blend(color2, color1, blendAmt) : blend(color1, color2, blendAmt);
    }

    FastLED.show();
}

// a value delta (typically +/- some small number) has been received from the encoder
void valueDelta(int delta)
{
    // state: 0=none, 1=hue, 2=sat, 3=val
    int state = 0;

    // determine state
    if (lastToggledPattern)
    {
        // toggled pattern, state is hue
        state = 1;
    }
    else
    {
        if (isPressedSat())
        {
            // saturation (if toggle pattern state, only edit hue)
            if (isPressedVal())
            {
                // sat + val - neither
            }
            else
            {
                // saturation
                state = 2;
            }
        }
        else if (isPressedVal())
        {
            // value
            state = 3;
        }
        else
        {
            // hue
            state = 1;
        }
    }

    // ignore unassigned state
    if (state == 0)
    {
        return;
    }

    int target = 0;

    switch (state)
    {
    case 1:
        // hue
        target = getCurrentColorH() + (delta * H_DELTA_MULT);
        setCurrentColorH((byte)target);
        break;

    case 2:
        // sat
        target = getCurrentColorS() + (delta * S_DELTA_MULT);
        if (target > 255)
        {
            target = 255;
        }
        else if (target < 0)
        {
            target = 0;
        }
        setCurrentColorS((byte)target);
        break;

    case 3:
        // val
        target = getCurrentColorV() + (delta * V_DELTA_MULT);
        if (target > MAX_BRIGHTNESS)
        {
            target = MAX_BRIGHTNESS;
        }
        else if (target < MIN_BRIGHTNESS)
        {
            target = MIN_BRIGHTNESS;
        }
        setCurrentColorV((byte)target);
        break;
    }

    if (state != 0)
    {
        updateLEDs();
    }
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
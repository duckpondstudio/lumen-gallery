#include "leds.h"

CRGB leds[LEDS_COUNT];

static byte color1H = DEFAULT_HUE_COLOR1;
static byte color1S = DEFAULT_SAT_COLOR1;
static byte color1V = DEFAULT_VAL_COLOR1;

static byte color2H = DEFAULT_HUE_COLOR2;
static byte color2S = DEFAULT_SAT_COLOR2;
static byte color2V = DEFAULT_VAL_COLOR2;

static bool currentColor2 = false;

static int currentPattern = PATTERN_CT_DEFAULT;
static bool patternInverted = false;

static bool lastToggledPattern = false;
static bool lastPressedEnc = false;

void setupLEDs()
{
    // FastLED.setBrightness(100);
    FastLED.addLeds<CHIPSET, PIN_LEDS, RGB_ORDER>(leds, LEDS_COUNT);

    // load intial values
    loadLEDData();

    // initial LED assignment
    updateLEDs(false);
}

void loadLEDData()
{

    if (!hasSaved())
    {
        // use initial save data
        return;
    }
    
    // load values 
    color1H = getSaveByte(0);
    color1S = getSaveByte(1);
    color1V = getSaveByte(2);
    color2H = getSaveByte(3);
    color2S = getSaveByte(4);
    color2V = getSaveByte(5);
    currentPattern = getSaveInt(0);
    patternInverted = getSaveBool(0);
    currentColor2 = getSaveBool(1);
}
void saveLEDData()
{
    // save values 
    setSaveByte(0, color1H);
    setSaveByte(1, color1S);
    setSaveByte(2, color1V);
    setSaveByte(3, color2H);
    setSaveByte(4, color2S);
    setSaveByte(5, color2V);
    setSaveInt(0, currentPattern);
    setSaveBool(0, patternInverted);
    setSaveBool(1, currentColor2);
}

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
            doubleButtonPush();
        }
    }

    // determine encoder state
    bool pressedEnc = isPressedEnc();
    if (pressedEnc != lastPressedEnc)
    {
        lastPressedEnc = pressedEnc;
        if (pressedEnc)
        {
            // pressed encoder down
            encoderPush();
        }
    }
}

// both buttons have been pressed
void doubleButtonPush()
{
    currentPattern++;
    if (currentPattern > PATTERN_CT_MAX)
    {
        currentPattern = PATTERN_CT_MIN;
    }
    updateLEDs();
}

// encoder button has been pressed
void encoderPush()
{
    // pressed encoder down
    // patternInverted = !patternInverted; // change inversion pattern
    currentColor2 = !currentColor2; // switch current color
    updateLEDs();
}

void updateLEDs(bool autoSave = true)
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

    if (autoSave) {
        saveLEDData();
    }
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
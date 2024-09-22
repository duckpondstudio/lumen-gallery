#include "main.h"

bool setupComplete;

void setup()
{
    delay(INITIAL_DELAY);

    if (DEBUG_INTERNAL_ENABLED)
    {
        setupDebug();
        if (DEBUG_INTERNAL_ONLY)
        {
            setupComplete = true;
            return;
        }
        delay(SETUP_STEP_DELAY);
    }

    if (ENABLE_SAVEDATA)
    {
        setupSaveData();

        delay(SETUP_STEP_DELAY);
    }

    if (ENABLE_INPUT)
    {
        setupInput();
        delay(SETUP_STEP_DELAY);
    }

    if (ENABLE_LEDS)
    {
        setupLEDs();
        delay(SETUP_STEP_DELAY);
    }

    setupComplete = true;
}

void loop()
{
    if (!setupComplete || !ENABLE_LOOP)
        return;

    if (DEBUG_INTERNAL_ENABLED)
    {
        loopDebug();
        if (DEBUG_INTERNAL_ONLY)
        {
            delay(1);
            return;
        }
    }

    if (ENABLE_INPUT)
        loopInput();

    if (ENABLE_LEDS)
        loopLEDs();

    if (ENABLE_SAVEDATA)
        loopSaveData();

    // loop delay
    delay(1);
}

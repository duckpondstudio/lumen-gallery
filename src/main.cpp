#include "main.h"

bool setupComplete;

void setup()
{
    delay(INITIAL_DELAY);

    if (DEBUG_ENABLED)
    {
        setupDebug();
        if (DEBUG_ONLY)
        {
            setupComplete = true;
            return;
        }
        delay(SETUP_STEP_DELAY);
    }

    // setupSaveData();

    // delay(SETUP_STEP_DELAY);

    // setupInput();

    // delay(SETUP_STEP_DELAY);

    // setupLEDs();

    setupComplete = true;
}

void loop()
{
    if (!setupComplete)
        return;

    if (DEBUG_ENABLED)
    {
        loopDebug();
        if (DEBUG_ONLY)
        {
            delay(1);
            return;
        }
    }

    // loopInput();
    // loopLEDs();
    // loopSaveData();

    // loop delay
    delay(1);
}

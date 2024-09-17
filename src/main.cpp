#include "main.h"

bool setupComplete;

void setup()
{
    delay(INITIAL_DELAY);

    setupSaveData();

    delay(SETUP_STEP_DELAY);

    setupInput();

    delay(SETUP_STEP_DELAY);
    
    setupLEDs();

    setupComplete = true;
}

void loop()
{
    if (!setupComplete)
        return;

    loopInput();
    loopLEDs();
    loopSaveData();

    // loop delay
    delay(1);
}

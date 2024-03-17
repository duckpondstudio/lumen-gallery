#include "main.h"

bool setupComplete;

void setup()
{
    delay(INITIAL_DELAY);

    setupSaveData();
    setupInput();
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

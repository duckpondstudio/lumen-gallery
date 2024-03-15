#include "main.h"

void setup()
{
    setupSaveData();
    setupInput();
    setupLEDs();
}

void loop()
{

    loopInput();
    loopLEDs();

    // loop delay
    delay(1);
}

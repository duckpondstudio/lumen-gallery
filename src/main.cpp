#include "main.h"

// put function declarations here:

int timerInput = 0;
int timerLEDs = 0;

void setup()
{
    // put your setup code here, to run once:
    setupInput();
    setupLEDs();
}

void loop()
{
    // increment timers 
    timerInput++;
    timerLEDs++;

    // check timeout 
    if (timerInput >= INTERVAL_INPUT) {
        timerInput = 0;
        loopInput();
    }
    if (timerLEDs >= INTERVAL_LEDS) {
        timerLEDs = 0;
        loopLEDs();
    }

    // loop delay
    delay(INTERVAL_LOOP);
}
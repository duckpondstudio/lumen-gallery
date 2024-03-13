#include "main.h"

// put function declarations here:

bool b = false;
bool ll = false;

void setup()
{
    // put your setup code here, to run once:
    setupInput();
    setupLEDs();
    // pinMode(1, OUTPUT);
    // digitalWrite(1, b ? HIGH : LOW);
}

// unsigned long previousInputMillisA = 0;
// unsigned long previousInputMillisB = 0;
void loop()
{
        // loopLEDs();

    // if (ll) {
    //     ll = false;
    // }

    loopInput();
    loopLEDs();

    // loop delay
    delay(1);
    
    // unsigned long currentMillis = millis();
    // if (currentMillis - previousInputMillisA >= 1500) {
    //     previousInputMillisA = currentMillis;
    //     ll = true;
    // }
    // if (currentMillis - previousInputMillisB >= 250) {
    //     previousInputMillisB = currentMillis;
    //     b = !b;
    // }
    // digitalWrite(1, b ? HIGH : LOW);

    // b = !b;
    // delay(500);
    // digitalWrite(1, b ? HIGH : LOW);
    // delay(500);
    // digitalWrite(1, b ? HIGH : LOW);
}

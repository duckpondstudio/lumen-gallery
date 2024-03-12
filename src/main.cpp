#include "main.h"

// put function declarations here:


void setup() {
  // put your setup code here, to run once:
  setupLEDs();
  setupInput();
}

void loop() {
  // put your main code here, to run repeatedly:
  loopInput();
  loopLEDs();

  delay(LOOP_INTERVAL);
}

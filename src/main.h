#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#include "debug.h"
#include "pindef.h"
#include "input.h"
#include "leds.h"
#include "savedata.h"

#define INITIAL_DELAY 20
#define SETUP_STEP_DELAY 10

#define ENABLE_LOOP false // enable loop() method? Used for debugging 

#define ENABLE_SAVEDATA false // Use SaveData? SaveData should be setup first and looped last 
#define ENABLE_LEDS true // Use LEDs? LEDs should be setup last and looped second 
#define ENABLE_INPUT false // Use Input? Input should be setup second and looped first 

#define DEBUG_ENABLED false // use debug systems / tools
#define DEBUG_ONLY true     // if DEBUG_ENABLED, exclude setup and loop for non-debug functions

void setup();
void loop();

#endif
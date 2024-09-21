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

#define ENABLE_SAVEDATA true // Use SaveData? SaveData should be setup first and looped last 
#define ENABLE_LEDS true // Use LEDs? LEDs should be setup last and looped second 
#define ENABLE_INPUT true // Use Input? Input should be setup second and looped first 

void setup();
void loop();

#endif
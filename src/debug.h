#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

#define DEBUG_ENABLED true // use debug systems / tools 
#define DEBUG_ONLY true // in main.h, if DEBUG_ENABLED, exclude setup and loop for non-debug functions 

void setupDebug();
void loopDebug();

#endif
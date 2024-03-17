#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <Arduino.h>
#include <eewl.h>
#include "leds.h"
#include "ledarrays.h"

#define DEFAULT_HUE_COLOR1 0 
#define DEFAULT_SAT_COLOR1 255
#define DEFAULT_VAL_COLOR1 100
#define DEFAULT_HUE_COLOR2 160
#define DEFAULT_SAT_COLOR2 255
#define DEFAULT_VAL_COLOR2 100
#define DEFAULT_PATTERN 1

#define CHECK_INDEX_VALIDITY false

#define FORCE_RESET false

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 12
#endif

#ifndef BUFFER_START
#define BUFFER_START 0x10
#endif

#ifndef SAVE_INTERVAL
#define SAVE_INTERVAL 1000 // min time in ms between saves
#endif


// container for all local savedata
struct saveData
{
    // have values previously been saved
    bool saved = false;
    byte color1H = DEFAULT_HUE_COLOR1;
    byte color1S = DEFAULT_SAT_COLOR1;
    byte color1V = DEFAULT_VAL_COLOR1;
    byte color2H = DEFAULT_HUE_COLOR2;
    byte color2S = DEFAULT_SAT_COLOR2;
    byte color2V = DEFAULT_VAL_COLOR2;
    int currentPattern = DEFAULT_PATTERN;
    bool patternInverted = false;
    bool currentColor2 = false;
};

void setupSaveData();
void loopSaveData();
void queueSaveData();
saveData *getSaveData();
void commitSaveData();

bool hasSaved();

#endif
#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <Arduino.h>
#include <eewl.h>

#define CHECK_INDEX_VALIDITY true

#ifndef SAVE_LENGTH_BOOL
#define SAVE_LENGTH_BOOL 2
#endif

#ifndef SAVE_LENGTH_BYTE
#define SAVE_LENGTH_BYTE 6
#endif

#ifndef SAVE_LENGTH_INT
#define SAVE_LENGTH_INT 1
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH SAVE_LENGTH_BOOL + SAVE_LENGTH_BYTE + (SAVE_LENGTH_INT * 2) + 1
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
    bool saved;
    // array for all bools storage
    bool boolData[SAVE_LENGTH_BOOL];
    // array for all bytes storage
    bool byteData[SAVE_LENGTH_BYTE];
    // array for all ints storage
    int intData[SAVE_LENGTH_INT];
};

void setupSaveData();
void loopSaveData();
void commitSaveData();

bool getSaveBool(int index);
void setSaveBool(int index, bool value, bool force = false);

byte getSaveByte(int index);
void setSaveByte(int index, byte value, bool force = false);

int getSaveInt(int index);
void setSaveInt(int index, int value, bool force = false);

bool hasSaved();

#endif
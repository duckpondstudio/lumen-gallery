#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <eewl.h>

#ifndef SAVE_LENGTH_INT
#define SAVE_LENGTH_INT 10
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH SAVE_LENGTH_INT + 1
#endif

#ifndef BUFFER_START
#define BUFFER_START 0x10
#endif

struct saveData {
    int intData[SAVE_LENGTH_INT];
};

void setupSaveData();

#endif
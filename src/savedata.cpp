#include "savedata.h"

saveData data;

EEWL eewlData(data, BUFFER_LENGTH, BUFFER_START);

void setupSaveData() {
    // begin EEWL object 
    eewlData.begin();

    // initial data get 
    if (eewlData.get(data)) {
        // data found 
    } else {
        // data not found, first run 
    }
}

bool hasSaved() {
    return data.saved;
}
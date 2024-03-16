#include "savedata.h"

saveData data;

EEWL eewlData(data, BUFFER_LENGTH, BUFFER_START);

void setupSaveData() {

    eewlData.begin();
}
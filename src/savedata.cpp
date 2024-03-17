#include "savedata.h"

#include "leds.h"

saveData data;

EEWL eewlData(data, BUFFER_LENGTH, BUFFER_START);

bool queuedSave = false;
int saveDelay = 0;

void setupSaveData()
{
    // begin EEWL object
    eewlData.begin();

    if (FORCE_RESET) {
        eewlData.fastFormat();
    }

    // initial data get
    if (eewlData.get(data))
    {
        // data found
        setDebugLight(true);
    }
    else
    {
        // data not found, first run
        data.saved = false;
    }
}

void loopSaveData()
{
    // decrement save delay
    if (saveDelay > 0)
    {
        saveDelay--;
    }
    // apply queued save state
    if (queuedSave)
    {
        if (saveDelay <= 0)
        {
            commitSaveData();
            queuedSave = false;
            saveDelay = SAVE_INTERVAL;
        }
    }
}

void commitSaveData()
{
    data.saved = true;
    eewlData.put(data);
}

bool hasSaved()
{
    return data.saved;
}
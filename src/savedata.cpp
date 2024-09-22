#include "savedata.h"

#include "leds.h"

saveData data;

EEWL eewlData(data, BUFFER_LENGTH, BUFFER_START);

bool queuedSave = false;
int saveDelay = 0;

void setupSaveData()
{
    if (!ENABLE_SAVEDATA)
    {
        // do not initialize save data
        // (technically redundant since setupSaveData never gets called,
        //  but I want to ensure the compiler doesn't bother with EEWL stuff)
        return;
    }

    // begin EEWL object
    eewlData.begin();

    if (FORCE_RESET)
    {
        eewlData.fastFormat();
    }

    // initial data get
    if (eewlData.get(data))
    {
        // data found
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
        return;
    }

    // apply queued save state
    if (queuedSave)
    {
        commitSaveData();
        queuedSave = false;
        saveDelay = SAVE_INTERVAL;
    }
}

void queueSaveData()
{
    queuedSave = true;
}

saveData *getSaveData()
{
    if (!ENABLE_SAVEDATA)
    {
        // if savedata is disabled, force set "saved" flag to true, to allow functionality w/o save
        data.saved = true;
    }
    return &data;
}

void commitSaveData()
{
    if (!ENABLE_SAVEDATA)
    {
        // can't write savedata if system is disabled (eewlData is uninitialized)
        return;
    }
    data.saved = true;
    eewlData.put(data);
}

bool hasSaved()
{
    if (!ENABLE_SAVEDATA)
    {
        // if savedata is disabled, "hasSaved" checks should always return true
        return true;
    }
    return data.saved;
}
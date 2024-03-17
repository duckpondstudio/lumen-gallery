#include "savedata.h"

saveData data;

EEWL eewlData(data, BUFFER_LENGTH, BUFFER_START);

bool queuedSave = false;
int saveDelay = 0;

void setupSaveData()
{
    // begin EEWL object
    eewlData.begin();

    // initial data get
    if (eewlData.get(data))
    {
        // data found
    }
    else
    {
        // data not found, first run
    }
}

void loopSaveData()
{
    // decrement save delay 
    if (saveDelay > 0) {
        saveDelay--;
    }
    // apply queued save state 
    if (queuedSave)
    {
        if (saveDelay <= 0) {
            eewlData.put(data);
            queuedSave = false;
            saveDelay = SAVE_INTERVAL;
        }
    }
}

int getInt(int index)
{
    if (CHECK_INDEX_VALIDITY)
    {
        if (index < 0)
        {
            // too low, return 0
            return 0;
        }
        else if (index >= SAVE_LENGTH_INT)
        {
            // too high, return 0
            return 0;
        }
    }
    return data.intData[index];
}
void setInt(int index, int value, bool force = false)
{
    if (CHECK_INDEX_VALIDITY)
    {
        if (index < 0)
        {
            // too low, return
            return;
        }
        else if (index >= SAVE_LENGTH_INT)
        {
            // too high, return
            return;
        }
    }

    data.intData[index] = value;

    queuedSave = true;

    if (force)
    {
        saveDelay = 0;
        loopSaveData();
    }
}

bool getBool(int index)
{
    if (CHECK_INDEX_VALIDITY)
    {
        if (index < 0)
        {
            // too low, return false
            return false;
        }
        else if (index >= SAVE_LENGTH_BOOL)
        {
            // too high, return false
            return false;
        }
    }
    return data.boolData[index];
}
void setBool(int index, bool value, bool force = false)
{
    if (CHECK_INDEX_VALIDITY)
    {
        if (index < 0)
        {
            // too low, return
            return;
        }
        else if (index >= SAVE_LENGTH_BOOL)
        {
            // too high, return
            return;
        }
    }

    data.boolData[index] = value;

    queuedSave = true;

    if (force)
    {
        saveDelay = 0;
        loopSaveData();
    }
}

bool hasSaved()
{
    return data.saved;
}
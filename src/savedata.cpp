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

bool getSaveBool(int index)
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
void setSaveBool(int index, bool value, bool force)
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

byte getSaveByte(int index)
{
    if (CHECK_INDEX_VALIDITY)
    {
        if (index < 0)
        {
            // too low, return false
            return false;
        }
        else if (index >= SAVE_LENGTH_BYTE)
        {
            // too high, return false
            return false;
        }
    }
    return data.byteData[index];
}
void setSaveByte(int index, byte value, bool force)
{
    if (CHECK_INDEX_VALIDITY)
    {
        if (index < 0)
        {
            // too low, return
            return;
        }
        else if (index >= SAVE_LENGTH_BYTE)
        {
            // too high, return
            return;
        }
    }

    data.byteData[index] = value;

    queuedSave = true;

    if (force)
    {
        saveDelay = 0;
        loopSaveData();
    }
}

int getSaveInt(int index)
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
void setSaveInt(int index, int value, bool force)
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

bool hasSaved()
{
    return data.saved;
}
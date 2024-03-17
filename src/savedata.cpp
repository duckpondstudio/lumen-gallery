#include "savedata.h"

saveData data;

EEWL eewlData(data, BUFFER_LENGTH, BUFFER_START);

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
void setInt(int index, int value, bool autoCommit = true)
{
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
void setBool(int index, bool value, bool autoCommit = true)
{
}

bool hasSaved()
{
    return data.saved;
}
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
    return data.intData[index];
}
void setInt(int index, int value, bool autoCommit = true)
{
}

bool getBool(int index)
{
    return data.boolData[index];
}
void setBool(int index, bool value, bool autoCommit = true)
{
}

bool hasSaved()
{
    return data.saved;
}
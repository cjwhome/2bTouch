#include "parseddata.h"

ParsedData::ParsedData()
{

}

ParsedData * ParsedData::manager = nullptr;

ParsedData * ParsedData::getManager()
{
    if(manager == nullptr)
    {
        manager = new ParsedData();
    }
    return manager;
}

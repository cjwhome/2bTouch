#include "uimanager.h"

UiManager * UiManager::manager = nullptr;

UiManager * UiManager::getManager()
{
    if(manager == nullptr)
    {
        manager = new UiManager();
    }
    return manager;
}

#include "GInputManager.h"

GInputManager* GInputManager::_instance = nullptr;

bool* GInputManager::getStatus() 
{ 
	return bKeyStatus; 
}

void GInputManager::onKeyDown(EInputStatus key) 
{ 
	bKeyStatus[key] = true; 
}

void GInputManager::onKeyUp(EInputStatus key) 
{ 
	bKeyStatus[key] = false; 
}

void GInputManager::killFocus()
{
	for (auto& i : bKeyStatus)
	{
		bKeyStatus[i] = false;
	}
}
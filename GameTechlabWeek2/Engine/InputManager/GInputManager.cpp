#include "GInputManager.h"

GInputManager* GInputManager::GetInstance()
{
	static GInputManager* InputManager = new GInputManager();
	return InputManager;
}

void GInputManager::SetKey(EInputStatus Key, bool Status)
{
	bKeyStatus[Key] = Status;
}

bool GInputManager::GetKey(EInputStatus Key)
{
	return bKeyStatus[Key];
}

void GInputManager::KillFocus()
{
	for (auto& i : bKeyStatus)
	{
		bKeyStatus[i] = false;
	}
}
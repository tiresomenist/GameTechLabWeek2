#pragma once

//각 오브젝트의 update에 대해서 InputManager::getInstance()->isKeyDown(EInputStatus)으로 조건 확인
//입력 추가시 EInputStatus 및 WndProc.h 업데이트

//Check the status of KeyInput by enum
class GInputManager {
public:
	static GInputManager* GetInstance();

	enum EInputStatus {
		EI_W,
		EI_A,
		EI_S,
		EI_D,
		EI_LMOUSE,
		EI_RMOUSE,
		KEY_COUNT
	};

	void SetKey(EInputStatus Key, bool Status);
	bool GetKey(EInputStatus Key);
	void KillFocus();
	void Update();

private:
	bool bKeyStatus[KEY_COUNT] = {};

	GInputManager() = default;
	~GInputManager() = default;
	GInputManager(const GInputManager&) = delete;
	GInputManager& operator=(const GInputManager&) = delete;
};

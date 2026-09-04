#pragma once

//각 오브젝트의 update에 대해서 InputManager::getInstance()->isKeyDown(EInputStatus)으로 조건 확인
//입력 추가시 EInputStatus 및 WndProc.h 업데이트

enum EInputStatus {
	W,
	A,
	S,
	D,
	LMOUSE,
	RMOUSE,
	KEY_COUNT
};

//Check the status of KeyInput by enum
class GInputManager {
public:
	GInputManager(const GInputManager&) = delete;
	GInputManager& operator = (const GInputManager&) = delete;
	static GInputManager* getInstance()
	{
		if (!_instance)
			_instance = new GInputManager();
		return _instance;
	};
	~GInputManager() = default;
private:
	GInputManager() = default;
	static GInputManager* _instance;
	bool bKeyStatus[KEY_COUNT] = {};

public:
	bool* getStatus();
	void onKeyDown(EInputStatus key);
	void onKeyUp(EInputStatus key);
	void killFocus();
	void Update();
};

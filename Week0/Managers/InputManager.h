#pragma once
#include "../Headers.h"

class CInputManager
{

private:
	CInputManager();
	CInputManager(const CInputManager& ref) {};
	CInputManager& operator=(const CInputManager& ref) {};
	~CInputManager() {};


public:
	static CInputManager& GetInstance();

	void	ReleaseSingleton();

	void	UpdateInput(MSG& msg);

	WPARAM	GetKeyDown();

	void	SetupInput();


private:
	static CInputManager* instance;

	WPARAM		m_iKey;

};


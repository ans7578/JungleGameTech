#pragma once
#include "../Headers.h"

#define KEYSIZE 256

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

	bool	GetKeyDown(WPARAM wParam);


	void	SetupInput();


private:
	static CInputManager* instance;

	bool	m_iKeys[KEYSIZE];

};


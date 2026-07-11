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

	void	Update();

	void	UpdateInput(MSG& msg);

	bool	GetKeyDown(WPARAM wParam);
	bool	GetKey(WPARAM wParam);

	bool	GetKeyUp(WPARAM wParam);


	void	SetupInput();


private:
	static CInputManager* instance;

	bool	m_bCurrentFrame[KEYSIZE];

	bool	m_bPrevFrame[KEYSIZE];

};


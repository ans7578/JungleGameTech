#pragma once
#include "../Headers.h"


class CGameManager
{

private:
	CGameManager();
	CGameManager(const CGameManager& ref) {};
	CGameManager& operator=(const CGameManager& ref) {};
	~CGameManager() {};


public:
	static CGameManager& GetInstance();

	void	ReleaseSingleton();

	void	Update();

	void	UpdateInput(MSG& msg);

	bool	GetKeyDown(WPARAM wParam);
	bool	GetKey(WPARAM wParam);

	bool	GetKeyUp(WPARAM wParam);


	void	SetupInput();


private:
	static CGameManager* instance;


};


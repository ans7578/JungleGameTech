#include "GameManager.h"


CGameManager* CGameManager::instance = nullptr;


CGameManager& CGameManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CGameManager();
	}

	return *instance;
}
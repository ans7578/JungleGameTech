#pragma once
#include "../Headers.h"


class CGameManager
{

private:
	CGameManager() = default;
	CGameManager(const CGameManager& ref) {};
	CGameManager& operator=(const CGameManager& ref) {};
	~CGameManager() = default;


public:
	static CGameManager& GetInstance();

	void	ReleaseSingleton() { delete instance; }

	void	SetDeltatTime(float deltaTime) { m_DeltaTime = deltaTime; }

	float	GetDeltaTime() { return m_DeltaTime; }

private:
	static CGameManager* instance;
	float				m_DeltaTime = 0.f;

};


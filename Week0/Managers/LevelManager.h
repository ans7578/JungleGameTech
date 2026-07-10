#pragma once
#include "../Headers.h"
#include "../Enums.h"

using namespace std;

class CLevelBase;
class URenderer;

class CLevelManager
{
private:
	CLevelManager();
	CLevelManager(const CLevelManager& ref) {};
	CLevelManager& operator=(const CLevelManager& ref) {};
	~CLevelManager() {};

public:
	static CLevelManager& GetInstance();
	
	void	ReleaseSingleton();
	void	SetupLevels();

	void	Init_Level();

	void	Update_Level();

	void	LateUpdate_Level();

	void	Render_Level(URenderer* renderer);

	void	Render_Debug();
private:
	void	CreateLevel(ELevel eLevel, const char* strLevelName, CLevelBase* pLevel);

private:
	static CLevelManager* instance;

	map<ELevel, std::pair<const char*, CLevelBase*>> m_mapLevels;

	pair<ELevel,CLevelBase*> m_pairCurrentLevel;

	ELevel	m_ePendingLevel = LEVEL_NONE;

};


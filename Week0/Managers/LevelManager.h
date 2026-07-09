#pragma once
#include "../Levels/LevelBase.h"

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

private:
	static CLevelManager* instance;
};


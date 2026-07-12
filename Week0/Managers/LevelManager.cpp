#include "LevelManager.h"
#include "../Render/URenderer.h"
#include "../Levels/LevelBase.h"
#include "../Levels/Level_BoundBall.h"
#include "../Levels/Level_MovementActor.h"
#include "../Levels/Level_Platformer.h"

CLevelManager* CLevelManager::instance = nullptr;


CLevelManager::CLevelManager()
{
	m_pairCurrentLevel = make_pair(LEVEL_NONE, nullptr);
}

CLevelManager& CLevelManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CLevelManager();
	}

	return *instance;
}

void CLevelManager::ReleaseSingleton()
{
	CLevelBase* level = nullptr;
	for (auto elem : m_mapLevels)
	{
		level = elem.second.second;

		level->Release_Level();

		delete level;
	}

	delete instance;
}

void CLevelManager::SetupLevels()
{
	CreateLevel(LEVEL_0, "BoundBall_0", new CLevel_BoundBall());
	CreateLevel(LEVEL_1, "MovementActor_0", new CLevel_MovementActor());
	CreateLevel(LEVEL_2, "Platformer_0", new CLevel_Platformer());

}

void CLevelManager::Init_Level()
{
	m_pairCurrentLevel.second->Init_Level();
}

void CLevelManager::Update_Level()
{
	if (m_ePendingLevel != LEVEL_NONE)
	{
		m_pairCurrentLevel.first = m_ePendingLevel;

		m_pairCurrentLevel.second->Release_Level();

		m_pairCurrentLevel.second = m_mapLevels[m_ePendingLevel].second;

		m_pairCurrentLevel.second->Init_Level();

		m_ePendingLevel = LEVEL_NONE;
	}
	m_pairCurrentLevel.second->Update_Level();
}

void CLevelManager::LateUpdate_Level()
{
	m_pairCurrentLevel.second->LateUpdate_Level();
}

void CLevelManager::Render_Level(URenderer* renderer)
{
	m_pairCurrentLevel.second->Render_Level(renderer);
}

void CLevelManager::Render_Debug()
{
	ImGui::Begin("Level Manager");
	{
		for (const auto& elem : m_mapLevels)
		{
			if (ImGui::Button(elem.second.first))
			{
				//현재 레벨에서 현재 레벨로넘어가는건 불가.
				if (m_pairCurrentLevel.first != elem.first)
				{
					m_ePendingLevel = elem.first;
				}
			}
		}
	}
	ImGui::End();

	m_pairCurrentLevel.second->RenderDebug_Level();
}

void CLevelManager::CreateLevel(ELevel eLevel, const char* strLevelName, CLevelBase* pLevel)
{
	m_mapLevels.insert
	(
		make_pair
		(
			eLevel,
			make_pair
			(
				strLevelName, pLevel
			)
		)
	);

	if (m_mapLevels.size() == 1)
	{
		m_pairCurrentLevel.first = eLevel;
		m_pairCurrentLevel.second = m_mapLevels.begin()->second.second;
	}

}

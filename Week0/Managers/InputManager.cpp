#include "InputManager.h"

CInputManager* CInputManager::instance = nullptr;

CInputManager::CInputManager()
{

}

CInputManager& CInputManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CInputManager();
	}

	return *instance;
}

void CInputManager::ReleaseSingleton()
{
	delete instance;
}

void CInputManager::UpdateInput(MSG& msg)
{
	m_iKey = 0;

	if (msg.message == WM_KEYDOWN)
	{
		m_iKey = msg.wParam;
	}
}

WPARAM CInputManager::GetKeyDown()
{
	return m_iKey;
}

void CInputManager::SetupInput()
{
}

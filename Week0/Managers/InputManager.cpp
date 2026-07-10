#include "InputManager.h"

CInputManager* CInputManager::instance = nullptr;

CInputManager::CInputManager()
{
	memset(m_iKeys, 0, KEYSIZE);
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

	if (msg.message == WM_KEYDOWN)
	{
		m_iKeys[msg.wParam] = true;
	}
	if (msg.message == WM_KEYUP)
	{
		m_iKeys[msg.wParam] = false;
	}
}

bool CInputManager::GetKeyDown(WPARAM wParam)
{
	return m_iKeys[wParam];
}

void CInputManager::SetupInput()
{
}

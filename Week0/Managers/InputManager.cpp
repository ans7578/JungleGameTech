#include "InputManager.h"

CInputManager* CInputManager::instance = nullptr;

CInputManager::CInputManager()
{
	memset(m_bCurrentFrame, 0, KEYSIZE);
	memset(m_bPrevFrame, 0, KEYSIZE);

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

void CInputManager::Update()
{
	memcpy(m_bPrevFrame, m_bCurrentFrame, KEYSIZE);
}

void CInputManager::UpdateInput(MSG& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		m_bCurrentFrame[msg.wParam] = true;
		
	}
	if (msg.message == WM_KEYUP)
	{
		m_bCurrentFrame[msg.wParam] = false;
	}
}

bool CInputManager::GetKey(WPARAM wParam)
{
	return m_bCurrentFrame[wParam];
}

bool CInputManager::GetKeyDown(WPARAM wParam)
{
	return m_bCurrentFrame[wParam] && !m_bPrevFrame[wParam];
}

bool CInputManager::GetKeyUp(WPARAM wParam)
{
	return !m_bCurrentFrame[wParam] && m_bPrevFrame[wParam];
}

void CInputManager::SetupInput()
{

}

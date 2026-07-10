#include "MovementActor.h"
#include "../Managers/InputManager.h"


AMovementActor::AMovementActor()
{
	m_moveAmount = 0.1f;

	SetSize(0.1f);
}

AMovementActor::~AMovementActor()
{
}

void AMovementActor::Update()
{

	if (CInputManager::GetInstance().GetKeyDown(VK_UP))
	{
		m_fPosition.y += m_moveAmount;
	}

	if (CInputManager::GetInstance().GetKeyDown(VK_DOWN))
	{
		m_fPosition.y -= m_moveAmount;
	}

	if (CInputManager::GetInstance().GetKeyDown(VK_RIGHT))
	{
		m_fPosition.x += m_moveAmount;
	}

	if (CInputManager::GetInstance().GetKeyDown(VK_LEFT))
	{
		m_fPosition.x -= m_moveAmount;
	}
}

const char* AMovementActor::GetName()
{
	if (m_strName.empty())
	{
		m_strName = "AMovementActor" + std::to_string(m_iRefCount);
	}

	return m_strName.c_str();
}

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

	if (CInputManager::GetInstance().GetKeyUp(VK_UP))
	{
		m_fPosition.y += m_moveAmount;
		m_iCallCount++;
	}

	if (CInputManager::GetInstance().GetKey(VK_DOWN))
	{
		m_fPosition.y -= m_moveAmount;
	}

	if (CInputManager::GetInstance().GetKey(VK_RIGHT))
	{
		m_fPosition.x += m_moveAmount;
	}

	if (CInputManager::GetInstance().GetKey(VK_LEFT))
	{
		m_fPosition.x -= m_moveAmount;
	}
}

void AMovementActor::RenderDebug()
{
	ImGui::Text("Call Count : %d", m_iCallCount);
}

const char* AMovementActor::GetName()
{
	if (m_strName.empty())
	{
		m_strName = "AMovementActor" + std::to_string(m_iRefCount);
	}

	return m_strName.c_str();
}

#include "MovementActor.h"
#include "../Managers/InputManager.h"


AMovementActor::AMovementActor()
{
	m_moveAmount = 0.1f;

	m_eActorType = ACTOR_PLAYER;

	
	GetTransform()->SetScale(XMFLOAT3(100.f, 100.f, 100.f));

}

AMovementActor::~AMovementActor()
{
}

void AMovementActor::Update()
{

	if (CInputManager::GetInstance().GetKey(VK_UP))
	{
		GetTransform()->Translation(XMFLOAT3(0.f, m_moveAmount, 0.f));
		m_iCallCount++;
	}

	if (CInputManager::GetInstance().GetKey(VK_DOWN))
	{
		GetTransform()->Translation(XMFLOAT3(0.f, -m_moveAmount, 0.f));
	}

	if (CInputManager::GetInstance().GetKey(VK_RIGHT))
	{
		GetTransform()->Translation(XMFLOAT3(m_moveAmount,0.f, 0.f));
	}

	if (CInputManager::GetInstance().GetKey(VK_LEFT))
	{
		GetTransform()->Translation(XMFLOAT3(-m_moveAmount, 0.f, 0.f));
	}
}

void AMovementActor::RenderDebug()
{
	__super::RenderDebug();
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

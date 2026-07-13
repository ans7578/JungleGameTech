#include "MovementActor.h"
#include "../Managers/InputManager.h"


AMovementActor::AMovementActor()
{
	m_moveAmount = 0.1f;

	GetTransform()->SetScale(XMFLOAT3(0.1f, 0.1f, 0.1f));
}

AMovementActor::~AMovementActor()
{
}

void AMovementActor::Update()
{
	
	if (CInputManager::GetInstance().GetKeyUp(VK_UP))
	{
		XMFLOAT3 position = GetTransform()->GetPosition();

		position.y += m_moveAmount;


		GetTransform()->SetPosition(position);
	}

	if (CInputManager::GetInstance().GetKey(VK_DOWN))
	{
		XMFLOAT3 position = GetTransform()->GetPosition();


		position.y -= m_moveAmount;
		GetTransform()->SetPosition(position);
	}

	if (CInputManager::GetInstance().GetKey(VK_RIGHT))
	{
		XMFLOAT3 position = GetTransform()->GetPosition();

		position.x += m_moveAmount;
		GetTransform()->SetPosition(position);
	}

	if (CInputManager::GetInstance().GetKey(VK_LEFT))
	{
		XMFLOAT3 position = GetTransform()->GetPosition();

		position.x -= m_moveAmount;
		GetTransform()->SetPosition(position);
	}
}

void AMovementActor::RenderDebug()
{
	
}

const char* AMovementActor::GetName()
{
	if (m_strName.empty())
	{
		m_strName = "AMovementActor" + std::to_string(m_iRefCount);
	}

	return m_strName.c_str();
}

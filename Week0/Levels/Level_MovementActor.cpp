#include "Level_MovementActor.h"
#include "../Actors/Actor.h"
#include "../Meshs/Mesh.h"
#include "../Enums.h"
#include "../Actors/MovementActor.h"

void CLevel_MovementActor::Init_Level()
{
	__super::Init_Level();

	AActor* actor = new AMovementActor();
	actor->SetMesh(EMeshType::CIRCLE);

	m_vecActors.push_back(actor);
}

void CLevel_MovementActor::Update_Level()
{
	for (auto actor : m_vecActors)
	{
		actor->Update();
	}

	XMFLOAT3 position;
	for (auto actor : m_vecActors)
	{
		position = actor->GetTransform()->GetPosition();
		float radius = actor->GetTransform()->GetScale().x;

		if (position.x < m_LeftBorder + radius)
		{
			position.x = m_LeftBorder + radius;
		}
		if (position.x > m_RightBorder - radius)
		{
			position.x = m_RightBorder - radius;
		}
		if (position.y > m_TopBorder - radius)
		{
			position.y = m_TopBorder - radius;
		}
		if (position.y < m_BottomBorder + radius)
		{
			position.y = m_BottomBorder + radius;
		}
		actor->GetTransform()->SetPosition(position);
	}
}

void CLevel_MovementActor::Render_Level(URenderer* renderer)
{
	__super::Render_Level(renderer);
}

void CLevel_MovementActor::Render_Debug()
{
	__super::Render_Debug();
}

void CLevel_MovementActor::Release_Level()
{
	__super::Release_Level();
}

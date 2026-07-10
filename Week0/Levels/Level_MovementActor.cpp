#include "Level_MovementActor.h"
#include "../Actors/Actor.h"
#include "../Meshs/Mesh.h"
#include "../Enums.h"
#include "../Actors/MovementActor.h"

void CLevel_MovementActor::Init_Level()
{
	AActor* actor = new AMovementActor();

	actor->SetMesh(EMeshType::CIRCLE_WHITE);

	m_vecActors.push_back(actor);
}

void CLevel_MovementActor::Update_Level()
{
	for (auto actor : m_vecActors)
	{
		actor->Update();
	}

	FVector pos;
	for (auto actor : m_vecActors)
	{
		pos = actor->GetPosition();
		float radius = actor->GetSize().x;

		if (pos.x < m_LeftBorder + radius)
		{
			pos.x = m_LeftBorder + radius;
		}
		if (pos.x > m_RightBorder - radius)
		{
			pos.x = m_RightBorder - radius;
		}
		if (pos.y > m_TopBorder - radius)
		{
			pos.y = m_TopBorder - radius;
		}
		if (pos.y < m_BottomBorder + radius)
		{
			pos.y = m_BottomBorder + radius;
		}
		actor->SetPosition(pos);
	}
}

void CLevel_MovementActor::Render_Level(URenderer* renderer)
{
	for (AActor* actor : m_vecActors)
	{
		renderer->UpdateConstantBuffer(actor->GetPosition());
		renderer->RenderPrimitiveIndexed(actor->GetMesh()->GetVertexBuffer(), actor->GetMesh()->GetIndexBuffer(), actor->GetMesh()->GetIndexCount());
	}
}

void CLevel_MovementActor::Render_Debug()
{
	__super::Render_Debug();
}

void CLevel_MovementActor::Release_Level()
{
	__super::Release_Level();
}

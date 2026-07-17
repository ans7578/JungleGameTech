#include "Level_MovementActor.h"
#include "../Actors/Actor.h"
#include "../Meshs/Mesh.h"
#include "../Enums.h"
#include "../Actors/MovementActor.h"

CLevel_MovementActor::CLevel_MovementActor()
{
	AActor* actor = new AMovementActor();
	actor->SetMesh(EMeshType::PRIMITIVE_RECT);

	m_vecActors.push_back(actor);
}

CLevel_MovementActor::~CLevel_MovementActor()
{

}

void CLevel_MovementActor::Init_Level()
{
	__super::Init_Level();
}

void CLevel_MovementActor::Update_Level()
{
	for (auto actor : m_vecActors)
	{
		actor->Update();
	}

	XMFLOAT3 pos;
	for (auto actor : m_vecActors)
	{
		if (actor->GetActorType() == ACTOR_CAMERA) continue;

		//pos = actor->GetTransform()->GetPosition();
		//float radius = actor->GetTransform()->GetScale().x;
		//
		//if (pos.x < m_LeftBorder + radius)
		//{
		//	pos.x = m_LeftBorder + radius;
		//}
		//if (pos.x > m_RightBorder - radius)
		//{
		//	pos.x = m_RightBorder - radius;
		//}
		//if (pos.y > m_TopBorder - radius)
		//{
		//	pos.y = m_TopBorder - radius;
		//}
		//if (pos.y < m_BottomBorder + radius)
		//{
		//	pos.y = m_BottomBorder + radius;
		//}
		//actor->GetTransform()->SetPosition(pos);
	}
}

void CLevel_MovementActor::Render_Level(URenderer* renderer)
{
	__super::Render_Level(renderer);
}

void CLevel_MovementActor::RenderDebug_Level()
{
	__super::RenderDebug_Level();
}

void CLevel_MovementActor::Release_Level()
{
	__super::Release_Level();
}

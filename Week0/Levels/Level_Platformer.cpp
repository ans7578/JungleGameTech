#include "Level_Platformer.h"
#include "../Utils.h"
#include "../Actors/APlatformerActor.h"

CLevel_Platformer::CLevel_Platformer()
{

}

CLevel_Platformer::~CLevel_Platformer()
{
}

void CLevel_Platformer::Init_Level()
{
	AActor* actor = new APlatformerActor();
		
	actor->SetMesh(EMeshType::PRIMITIVE_RECT);

	m_vecActors.push_back(actor);
}

void CLevel_Platformer::Update_Level()
{
	//for (auto actor : m_vecActors)
	//{
	//	actor->Update();
	//
	//	//업데이트 직후 공이 지면을 뚫었다면 다시 올려줌
	//	float groundCheckHeight = actor->GetPosition().y + actor->GetVelocity().y;
	//	if (groundCheckHeight < 100.f)
	//	{
	//		FVector pos = actor->GetPosition();
	//
	//		pos.y = 100.f;
	//		
	//		actor->SetPosition(pos);
	//
	//		actor->SetVelocity(0.f);
	//	}
	//}
}

void CLevel_Platformer::LateUpdate_Level()
{
	__super::LateUpdate_Level();

	//DirectX::XMFLOAT2 ndcPos;
	//for (auto actor : m_vecActors)
	//{
	//	FVector pos = actor->GetPosition();
	//
	//	ndcPos = Utils::ConvertScreenToNDC(pos.x, pos.y, 1024, 1024);
	//
	//	pos.x = ndcPos.x;
	//	pos.y = ndcPos.y;
	//
	//	actor->GetConstantBuffer().Offset = pos;
	//}
}

void CLevel_Platformer::Render_Level(URenderer* renderer)
{
	__super::Render_Level(renderer);
}

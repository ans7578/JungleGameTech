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
	__super::Init_Level();

	AActor* actor = new APlatformerActor();
		
	actor->SetMesh(EMeshType::CIRCLE);

	m_vecActors.push_back(actor);
}

void CLevel_Platformer::Update_Level()
{
	for (auto actor : m_vecActors)
	{
		actor->Update();

		APlatformerActor* platformerActor = dynamic_cast<APlatformerActor*>(actor);

		if (platformerActor == nullptr)
			continue;

		//업데이트 직후 공이 지면을 뚫었다면 다시 올려줌
		float groundCheckHeight = platformerActor->GetTransform()->GetPosition().y + platformerActor->GetVelocity().y;
		if (groundCheckHeight < 100.f)
		{
			XMFLOAT3 position = platformerActor->GetTransform()->GetPosition();

			position.y = 100.f;
			
			platformerActor->GetTransform()->SetPosition(position);

			platformerActor->SetVelocity(XMFLOAT3(0.f, 0.f, 0.f));
		}
	}
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

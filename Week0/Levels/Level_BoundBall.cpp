#include "Level_BoundBall.h"
#include "../Meshs/Mesh.h"
#include "../Managers/ResourceManager.h"
#include "../Actors/BoundActor.h"
#include "../Actors/Camera/CameraActor.h"


CLevel_BoundBall::CLevel_BoundBall()
{

}

CLevel_BoundBall::~CLevel_BoundBall()
{
}

void CLevel_BoundBall::Init_Level()
{
	for (const auto& actor : m_vecActors)
	{
		actor->Init();
	}
}

void CLevel_BoundBall::Update_Level()
{
	ABoundActor* boundActor;
	for (AActor* actor : m_vecActors)
	{
		actor->Update();

		float renderRadius = sphereRadius * 0.1;

		boundActor = dynamic_cast<ABoundActor*>(actor);

		if (boundActor == nullptr) continue;

		XMFLOAT3 veclotiy = boundActor->GetVelocity();

		XMFLOAT3 position = actor->GetTransform()->GetPosition();

		if (position.x < leftBorder + renderRadius)
		{
			veclotiy.x = veclotiy.x * -1.f;

			boundActor->SetVelocity(veclotiy);

		}
		else if (position.x > rightBorder - renderRadius)
		{
			veclotiy.x = veclotiy.x * -1.f;

			boundActor->SetVelocity(veclotiy);

		}

		if (position.y > topBorder - renderRadius)
		{
			veclotiy.y = veclotiy.y * -1.f;

			boundActor->SetVelocity(veclotiy);

		}
		else if (position.y < bottomBorder + renderRadius)
		{
			veclotiy.y = veclotiy.y * -1.f;
		
			boundActor->SetVelocity(veclotiy);
		}
	}
}

void CLevel_BoundBall::Render_Level(URenderer* renderer)
{
	__super::Render_Level(renderer);
}

void CLevel_BoundBall::Release_Level()
{
	__super::Release_Level();
}

void CLevel_BoundBall::RenderDebug_Level()
{
	__super::RenderDebug_Level();

	ImGui::Begin("BoundBall Window");
	{
		ImGui::Text("Hello Jungle World!");
		if (ImGui::Button("CreateCircle"))
		{
			if (m_vecActors.size() > 0)
			{
				//하얀색 공 생성
				m_vecActors.back()->SetMesh(EMeshType::PRIMITIVE_CIRCLE);
				m_vecActors.back()->SetColor(FColor(1.f, 1.f, 1.f, 1.f));
			}
			AActor* actor = new ABoundActor();
			actor->SetMesh(EMeshType::PRIMITIVE_CIRCLE);

			actor->SetColor(FColor(1.f, 0.f, 0.f, 1.f));
			
			m_vecActors.push_back(actor);
		}
	}
	ImGui::End();
}

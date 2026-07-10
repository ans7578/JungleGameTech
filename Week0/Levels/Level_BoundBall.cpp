#include "Level_BoundBall.h"
#include "../Meshs/Mesh.h"
#include "../Managers/ResourceManager.h"
#include "../Actors/BoundActor.h"



void CLevel_BoundBall::Init_Level()
{
	
}

void CLevel_BoundBall::Update_Level()
{



	for (AActor* actor : m_vecActors)
	{
		actor->Update();

		

		float renderRadius = sphereRadius * 0.1;

		FVector veclotiy = actor->GetVelocity();

		if (actor->GetPosition().x < leftBorder + renderRadius)
		{
			veclotiy.x = veclotiy.x * -1.f;
			actor->SetVelocity(veclotiy);

		}
		if (actor->GetPosition().x > rightBorder - renderRadius)
		{
			veclotiy.x = veclotiy.x * -1.f;
			actor->SetVelocity(veclotiy);

		}
		if (actor->GetPosition().y > topBorder - renderRadius)
		{
			veclotiy.y = veclotiy.y * -1.f;
			actor->SetVelocity(veclotiy);

		}
		if (actor->GetPosition().y < bottomBorder + renderRadius)
		{
			veclotiy.y = veclotiy.y * -1.f;
			actor->SetVelocity(veclotiy);
		}
	}
}

void CLevel_BoundBall::Render_Level(URenderer* renderer)
{
	for (AActor* actor : m_vecActors)
	{
		renderer->UpdateConstantBuffer(actor->GetPosition());
		renderer->RenderPrimitiveIndexed(actor->GetMesh()->GetVertexBuffer(), actor->GetMesh()->GetIndexBuffer(), actor->GetMesh()->GetIndexCount());
	}
}

void CLevel_BoundBall::Release_Level()
{
	__super::Release_Level();
}

void CLevel_BoundBall::Render_Debug()
{
	__super::Render_Debug();

	ImGui::Begin("BoundBall Window");
	{
		ImGui::Text("Hello Jungle World!");
		if (ImGui::Button("CreateCircle"))
		{
			if (m_vecActors.size() > 0)
			{
				//하얀색 공 생성
				m_vecActors.back()->SetMesh(EMeshType::CIRCLE_WHITE);
		
			}
			AActor* actor = new ABoundActor();
			actor->SetMesh(EMeshType::CIRCLE_RED);
			m_vecActors.push_back(actor);
		}
	}
	ImGui::End();
}

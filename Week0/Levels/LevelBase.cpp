#include "LevelBase.h"
#include "../Meshs/Mesh.h"

CLevelBase::CLevelBase()
{

}

CLevelBase::~CLevelBase()
{
	
}

void CLevelBase::Init_Level()
{
	for (auto actor : m_vecActors)
	{
		actor->Init();
	}
}

void CLevelBase::LateUpdate_Level()
{
	for (auto actor : m_vecActors)
	{
		actor->LateUpdate();
	}
}

void CLevelBase::Render_Level(URenderer* renderer)
{
	for (auto actor : m_vecActors)
	{
		actor->Render(renderer);
	
	}
}

void CLevelBase::Render_Debug()
{
	ImGui::Begin("Inspector");
	{
		for (AActor* actor : m_vecActors)
		{
			ImGui::PushID(actor);
			{
				if (ImGui::CollapsingHeader(actor->GetName()))
				{
				

					FColor color = actor->GetColor();

					float colorArray[3] = { color.r, color.g, color.b };

					if (ImGui::ColorEdit3("color", colorArray))
					{
						actor->SetColor(FColor(colorArray[0], colorArray[1], colorArray[2]));
					}
					actor->RenderDebug();
				}
			}
			ImGui::PopID();
		}
	}
	ImGui::End();
}

void CLevelBase::Release_Level()
{
	for (int i = m_vecActors.size() - 1; i >= 0; i--)
	{
		delete m_vecActors[i];
		m_vecActors.erase(m_vecActors.begin() + i);
	}
}

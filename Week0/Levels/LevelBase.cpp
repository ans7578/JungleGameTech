#include "LevelBase.h"

CLevelBase::CLevelBase()
{

}

CLevelBase::~CLevelBase()
{
	
}

void CLevelBase::LateUpdate_Level()
{
	for (auto elem : m_vecActors)
	{
		elem->LateUpdate();
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
					ImGui::Text("X : %f, Y : %f", actor->GetPosition().x, actor->GetPosition().y);

					FColor color = actor->GetColor();

					float colorArray[3] = { color.r, color.g, color.b };

					if (ImGui::ColorEdit3("color", colorArray))
					{
						actor->SetColor(FColor(colorArray[0], colorArray[1], colorArray[2]));
					}
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

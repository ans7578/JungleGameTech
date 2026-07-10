#include "LevelBase.h"

CLevelBase::CLevelBase()
{

}

CLevelBase::~CLevelBase()
{

}

void CLevelBase::Render_Debug()
{
	ImGui::Begin("Inspector");
	{
		for (AActor* actor : m_vecActors)
		{
			if (ImGui::CollapsingHeader(actor->GetName()))
			{
				ImGui::Text("X : %f, Y : %f", actor->GetPosition().x, actor->GetPosition().y);
			}
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

#include "BoundActor.h"
#include <string>


ABoundActor::ABoundActor()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	XMFLOAT3 position = XMFLOAT3(0.f, 0.f, 0.f);

	//좌표를  NDC 영역(-1~1) 으로 변환
	position.x = ((float)(rand() % 160) + 20.f) * 0.01f - 1.f;
	position.y = ((float)(rand() % 160) + 20.f) * 0.01f - 1.f;

	m_fVelocity.x = ((float)(rand() % 100 - 50)) * 0.001f;
	m_fVelocity.y = ((float)(rand() % 100 - 50)) * 0.001f;


	GetTransform()->SetPosition(position);


	GetTransform()->SetScale(XMFLOAT3(0.1f, 0.1f, 0.1f));

}

ABoundActor::~ABoundActor()
{
}

void ABoundActor::Update()
{
	__super::Update();

	GetTransform()->Translation(m_fVelocity);
}

const char* ABoundActor::GetName()
{
	if (m_strName.empty())
	{
		m_strName = "ABoundActor" + std::to_string(m_iRefCount);
	}

	return m_strName.c_str();
}

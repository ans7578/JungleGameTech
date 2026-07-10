#include "BoundActor.h"
#include <string>


ABoundActor::ABoundActor()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//좌표를  NDC 영역(-1~1) 으로 변환
	m_fPosition.x = ((float)(rand() % 160) + 20.f) * 0.01f - 1.f;
	m_fPosition.y = ((float)(rand() % 160) + 20.f) * 0.01f - 1.f;

	m_fVelocity.x = ((float)(rand() % 100 - 50)) * 0.001f;
	m_fVelocity.y = ((float)(rand() % 100 - 50)) * 0.001f;
}

ABoundActor::~ABoundActor()
{
}

void ABoundActor::Update()
{
	__super::Update();

	m_fPosition += m_fVelocity;
}

const char* ABoundActor::GetName()
{

	if (m_strName.empty())
	{
		m_strName = "ABoundActor" + std::to_string(m_iRefCount);
	}

	return m_strName.c_str();
}

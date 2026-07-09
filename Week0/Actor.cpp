#include "Actor.h"
#include "./Managers/ResourceManager.h"
#include "Mesh.h"

AActor::AActor()
{	
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//좌표를  NDC 영역(-1~1) 으로 변환
	m_vPosition.x = ((float)(rand() % 160) + 20.f) * 0.01f - 1.f;
	m_vPosition.y = ((float)(rand() % 160) + 20.f) * 0.01f - 1.f;

	m_vVelocity.x = ((float)(rand() % 100 - 50)) * 0.001f;
	m_vVelocity.y = ((float)(rand() % 100 - 50)) * 0.001f;
}

AActor::~AActor()
{

}

void AActor::Update()
{
	m_vPosition += m_vVelocity;
}

void AActor::SetMesh(EMeshType eMeshType)
{
	m_pMesh = CResourceManager::GetInstance().GetMesh(eMeshType);
}


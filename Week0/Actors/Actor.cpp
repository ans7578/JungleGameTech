#include "Actor.h"
#include "../Managers/ResourceManager.h"
#include "../Meshs/Mesh.h"

UINT AActor::m_iRefCount = 0;

AActor::AActor()
{	
	m_iRefCount++;
}

AActor::~AActor()
{
	m_iRefCount--;
}

void AActor::Update()
{
	
}

void AActor::SetMesh(EMeshType eMeshType)
{
	m_pMesh = CResourceManager::GetInstance().GetMesh(eMeshType);
}


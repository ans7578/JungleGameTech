#include "ResourceManager.h"
#include "../Render/URenderer.h"
#include "../Meshs/Mesh.h"
#include "../Meshs/Primitive/Circle.h"
#include "../Meshs/Primitive/Rect.h"

// 1. static 멤버 변수는 반드시 .cpp 파일에서 실체화 및 초기화를 해줘야 한다.
CResourceManager* CResourceManager::instance = nullptr;

CResourceManager::CResourceManager()
{

}

CResourceManager& CResourceManager::GetInstance()
{
	if (instance == nullptr)
	{ 
		instance = new CResourceManager();
	}

	return *instance;
}


CMesh* CResourceManager::GetMesh(EMeshType eResourceType)
{
	return m_mapResources[eResourceType];
}


void CResourceManager::ReleaseSingleton()
{
	for (std::pair<EMeshType, CMesh*> elem : m_mapResources)
	{
		delete	elem.second;
	}
	m_mapResources.clear();

	if (instance != nullptr)
	{
		delete instance;
	}
}

void CResourceManager::SetupResource(URenderer* renderer)
{

	//렌더러와 쉐이더 생성 이후 버텍스 버퍼를 생성한다.
	CirclePrimitive circlePrimitive;
	
	RectPrimitive rectPrimitive;

	//m_mapResources.insert(make_pair(PRIMITIVE_CIRCLE, new CMesh(renderer, 
	//	circlePrimitive.vertices, circlePrimitive.GetVertexStride(), circlePrimitive.GetVertexCount(),
	//	circlePrimitive.indices, circlePrimitive.indexCount)));



	m_mapResources.insert(make_pair(EMeshType::PRIMITIVE_RECT, new CMesh(renderer,
		rectPrimitive.vertices, rectPrimitive.GetVertexStride(), rectPrimitive.GetVertexCount(),
		rectPrimitive.indices, rectPrimitive.indexCount)));


	int a = rectPrimitive.GetVertexStride();


}

#include "ResourceManager.h"
#include "../Render/URenderer.h"
#include "../Meshs/Mesh.h"
#include "../Meshs/Primitive/Circle.h"
#include "../Meshs/Primitive/Rect.h"
#include "../Structs.h"


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
	return m_meshes[eResourceType];
}


void CResourceManager::ReleaseSingleton()
{
	for (std::pair<EMeshType, CMesh*> elem : m_meshes)
	{
		delete	elem.second;
	}
	m_meshes.clear();

	if (instance != nullptr)
	{
		delete instance;
	}
}

void CResourceManager::SetupPrimitive(URenderer* renderer)
{


	//렌더러와 쉐이더 생성 이후 버텍스 버퍼를 생성한다.
	CirclePrimitive circlePrimitive;
	
	RectPrimitive rectPrimitive;

	m_meshes.insert(make_pair(PRIMITIVE_CIRCLE, new CMesh(renderer,
		circlePrimitive.vertices, circlePrimitive.GetVertexStride(), circlePrimitive.GetVertexCount(),
		circlePrimitive.indices, circlePrimitive.indexCount)));

	m_meshes.insert(make_pair(EMeshType::PRIMITIVE_RECT, new CMesh(renderer,
		rectPrimitive.vertices, rectPrimitive.GetVertexStride(), rectPrimitive.GetVertexCount(),
		rectPrimitive.indices, rectPrimitive.indexCount)));

}


HRESULT CResourceManager::AddShaderPrograms(const wchar_t* szShaderName, const wchar_t* szShaderPath, URenderer* pRenderer)
{

	FShaderProgram* pShaderProgram = new FShaderProgram();


	pRenderer->CreateShader(szShaderPath,
		pShaderProgram->pVertexShader.GetAddressOf(),
		pShaderProgram->pPixelShader.GetAddressOf(),
		pShaderProgram->pInputLayout.GetAddressOf());


	m_ShaderPrograms.insert
	(
		make_pair
		(
			FStringToHash::Hash(szShaderName), pShaderProgram
		)
	);


	return S_OK;
}

bool CResourceManager::AddTexture(const wchar_t* szFileName, const wchar_t* szFilePath, URenderer* renderer)
{
	ComPtr<ID3D11ShaderResourceView> texture = nullptr;

	renderer->CreateShaderResources(szFilePath, texture.GetAddressOf());

	if (texture.Get() == nullptr)
	{
		return false;
	}

	m_textures.insert(
		make_pair(
			FStringToHash::Hash(szFileName),
			texture
		));

	return true;
}

const weak_ptr<FShaderProgram>& CResourceManager::LoadShaderProgram(const wchar_t* szFileName)
{
	HASH_KEY key = FStringToHash::Hash(szFileName);

	if (m_ShaderPrograms.find(key) != m_ShaderPrograms.end())
	{
		return m_ShaderPrograms[key];
	}
}

ComPtr<ID3D11ShaderResourceView>& CResourceManager::LoadTexture(const wchar_t* szFileName)
{
	HASH_KEY key = FStringToHash::Hash(szFileName);

	if (m_textures.find(key) != m_textures.end())
	{
		return m_textures[key];
	}
}



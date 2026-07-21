#include "ResourceManager.h"
#include "../Render/URenderer.h"
#include "../Meshs/Mesh.h"
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

void CResourceManager::ReleaseSingleton()
{
	

	for (std::pair<HASH_KEY, weak_ptr<CMesh>> elem : m_meshes)
	{
		elem.second.reset();
	}
	m_meshes.clear();

	if (instance != nullptr)
	{
		delete instance;
	}
}

void CResourceManager::AddMesh(const wchar_t* szMeshName, shared_ptr<CMesh> pMesh)
{
	//외부에서 생성한 메쉬의 소유권을 이전받는다
	shared_ptr<CMesh> mesh = std::move(pMesh);

	m_meshes.insert(make_pair
	(
		FStringToHash::Hash(szMeshName),
		mesh
	));
}

void CResourceManager::AddMaterials(const wchar_t* szMaterialName, shared_ptr<UMaterialBase> pMesh)
{
	//외부에서 생성한 메쉬의 소유권을 이전받는다
	shared_ptr<UMaterialBase> mesh = std::move(pMesh);

	m_materials.insert(make_pair
	(
		FStringToHash::Hash(szMaterialName),
		mesh
	));
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

weak_ptr<FShaderProgram> CResourceManager::LoadShaderProgram(const wchar_t* szFileName)
{
	HASH_KEY key = FStringToHash::Hash(szFileName);

	if (m_ShaderPrograms.find(key) != m_ShaderPrograms.end())
	{
		return m_ShaderPrograms[key];
	}
}

ComPtr<ID3D11ShaderResourceView> CResourceManager::LoadTexture(const wchar_t* szFileName)
{
	HASH_KEY key = FStringToHash::Hash(szFileName);

	if (m_textures.find(key) != m_textures.end())
	{
		return m_textures[key];
	}
}

weak_ptr<CMesh> CResourceManager::LoadMesh(const wchar_t* szMeshName)
{
	return m_meshes[FStringToHash::Hash(szMeshName)];
}
	
weak_ptr<UMaterialBase> CResourceManager::LoadMaterial(const wchar_t* szMaterialName)
{
	return m_materials[FStringToHash::Hash(szMaterialName)];
}



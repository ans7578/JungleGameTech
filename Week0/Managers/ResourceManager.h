#pragma once
#include "../Headers.h"
#include "../Structs.h"
#include "../Enums.h"

class URenderer;
class CMesh;
class UMaterialBase;

using namespace std;

typedef unsigned long long HASH_KEY;

class CResourceManager
{
private:
	CResourceManager();
	CResourceManager(const CResourceManager& ref) {};
	CResourceManager& operator=(const CResourceManager& ref) {};
	~CResourceManager() = default;

public:
	static CResourceManager& GetInstance();
	void	ReleaseSingleton();

	//버텍스버퍼 정보를 담은 녀석.

	
	void	AddMesh(const wchar_t* szMeshName,shared_ptr<CMesh>pMesh);

	void	AddMaterials(const wchar_t* szMaterialName, shared_ptr<UMaterialBase>pMaterial);
	
	HRESULT	AddShaderPrograms(const wchar_t* szShaderName, const wchar_t* szShaderPath, URenderer* pRenderer);

	bool	AddTexture(const wchar_t* szFileName, const wchar_t* szFilePath, URenderer* renderer);


	weak_ptr<FShaderProgram> LoadShaderProgram(const wchar_t* szFileName);

	ComPtr<ID3D11ShaderResourceView> LoadTexture(const wchar_t* szFileName);

	weak_ptr<CMesh> LoadMesh(const wchar_t* szMeshName);

	weak_ptr<UMaterialBase> LoadMaterial(const wchar_t* szMaterialName);


private:
	static CResourceManager* instance;
	
	unordered_map<HASH_KEY, shared_ptr<CMesh>> m_meshes;

	unordered_map<HASH_KEY, shared_ptr<UMaterialBase>> m_materials;

	unordered_map<HASH_KEY, ComPtr<ID3D11ShaderResourceView>> m_textures;

	unordered_map<HASH_KEY, shared_ptr<FShaderProgram>> m_ShaderPrograms;

};

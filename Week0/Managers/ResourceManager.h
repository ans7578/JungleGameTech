#pragma once
#include "../Headers.h"
#include "../Structs.h"
#include "../Enums.h"

class URenderer;
class CMesh;
class UMaterial;

using namespace std;

typedef unsigned long long HASH_KEY;

class CResourceManager
{
private:
	CResourceManager();
	CResourceManager(const CResourceManager& ref) {};
	CResourceManager& operator=(const CResourceManager& ref) {};
	~CResourceManager() {};

public:
	static CResourceManager& GetInstance();


	//버텍스버퍼 정보를 담은 녀석.
	CMesh* GetMesh(EMeshType eMeshType);

	void	ReleaseSingleton();

	void	SetupPrimitive(URenderer* renderer);

	
	HRESULT	AddShaderPrograms(const wchar_t* szShaderName, const wchar_t* szShaderPath, URenderer* pRenderer);



	bool	AddTexture(const wchar_t* szFileName, const wchar_t* szFilePath, URenderer* renderer);

	const weak_ptr<FShaderProgram>& LoadShaderProgram(const wchar_t* szFileName);

	ComPtr<ID3D11ShaderResourceView>& LoadTexture(const wchar_t* szFileName);


private:


private:
	static CResourceManager* instance;
	
	map<EMeshType, CMesh*> m_meshes;

	unordered_map<HASH_KEY, ComPtr<ID3D11ShaderResourceView>> m_textures;

	unordered_map<HASH_KEY, shared_ptr<FShaderProgram>> m_ShaderPrograms;

	
};


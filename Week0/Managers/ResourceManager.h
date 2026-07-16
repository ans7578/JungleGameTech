#pragma once
#include "../Headers.h"
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
	void	SetupResource(URenderer* renderer);


	void	LoadTexture(const wchar_t* szFileName, const wchar_t* szFilePath, URenderer* renderer);

private:
	static CResourceManager* instance;
	
	map<EMeshType, CMesh*> m_meshes;

	unordered_map<HASH_KEY, ID3D11ShaderResourceView*> m_textures;


	
};


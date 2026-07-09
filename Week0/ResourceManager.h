#pragma once
#include "Headers.h"


class URenderer;
class CMesh;


using namespace std;


enum EMeshType
{
	CIRCLE_WHITE,
	CIRCLE_RED
};


class CResourceManager
{
private:
	CResourceManager();
	CResourceManager(const CResourceManager& ref) {};
	CResourceManager& operator=(const CResourceManager& ref) {};
	~CResourceManager() {};

public:
	static CResourceManager& GetInstance();


	CMesh* GetMesh(EMeshType eMeshType);

	void	ReleaseSingleton();
	void	SetupResource(URenderer* renderer);




private:
	static CResourceManager* instance;
	
	map<EMeshType, CMesh*> m_mapResources;
};


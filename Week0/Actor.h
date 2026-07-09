#pragma once
#include "Headers.h"
#include "URenderer.h"


class CMesh;

class AActor
{
public:
	AActor();
	~AActor();

public:
	void Update();

	
	CMesh*			GetMesh() { return m_pMesh; }
	FVector			GetPosition() { return m_vPosition; }
	FVector			GetVelocity() { return m_vVelocity; }
	


	void			SetMesh(EMeshType eMeshType);
	void			SetVelocity(FVector fVelocity) { m_vVelocity = fVelocity; }

private:
	FVector m_vPosition = FVector(0.f,0.f,0.f);
	FVector m_vVelocity = FVector(0.f, 0.f, 0.f);

	UINT m_iIndicesCount = 0;

	CMesh* m_pMesh;

};


#pragma once
#include "Headers.h"
#include "URenderer.h"


class AActor
{
public:
	AActor(URenderer* Renderer, FVertexSimple* fVertices, 
		UINT iVerticesData,
		UINT*	 iIndices, 
		UINT	iIndicesData);
	~AActor();


public:
	void Update();

	void			SetBuffer(URenderer* Renderer, FVertexSimple* fVertices,
		UINT iVerticesData,
		UINT* iIndices,
		UINT	iIndicesData);


	ID3D11Buffer*	GetVertexBuffer() { return m_pVertexBuffer; }
	ID3D11Buffer*	GetIndexBuffer() { return m_pIndexBuffer; }
	UINT			GetIndicesCount() { return m_iIndicesCount; }

	FVector			GetPosition() { return m_vPosition; }

	FVector			GetVelocity() { return m_vVelocity; }
	void			SetVelocity(FVector fVelocity) { m_vVelocity = fVelocity; }

private:
	FVector m_vPosition = FVector(0.f,0.f,0.f);
	FVector m_vVelocity = FVector(0.f, 0.f, 0.f);

	UINT m_iIndicesCount = 0;

	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;

};


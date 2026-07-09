#pragma once
#include "Headers.h"

class URenderer;

class CMesh
{

private:
	friend class CResourceManager;

	CMesh(URenderer* renderer, FVertexSimple* vertices, UINT verticesSize, UINT* indices,  UINT indexCount);
	~CMesh();

	CMesh(const CMesh& ref) = default;
	CMesh& operator=(const CMesh& ref) = default;
		

public:
	ID3D11Buffer*	GetVertexBuffer() { return m_pVertexBuffer; }
	
	ID3D11Buffer*	GetIndexBuffer() { return m_pIndexBuffer; }
	
	UINT			GetVertexStride() { return m_iVertexStride; }

	UINT			GetVerticesSize() { return m_iVerticesSize; }

	UINT			GetIndexCount() { return m_iIndexCount; }

protected:
	ID3D11Buffer*	m_pVertexBuffer;
	ID3D11Buffer*	m_pIndexBuffer;

	ID3D11Buffer*	m_constantBuffer;

	UINT			m_iVertexStride; // 객체 하나의 사이즈

	UINT			m_iVerticesSize;
	UINT			m_iIndexCount;

};


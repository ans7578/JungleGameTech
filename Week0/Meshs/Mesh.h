#pragma once
#include "../Headers.h"

class URenderer;

class CMesh
{

public:
	CMesh(URenderer* renderer, void* pVertexData, UINT iVertexStride, UINT iVertexCount , UINT* pIndexData,  UINT indexCount);
	~CMesh();

	CMesh(const CMesh& ref) = default;
	CMesh& operator=(const CMesh& ref) = default;
		

public:
	ID3D11Buffer* GetVertexBuffer();
	
	ID3D11Buffer* GetIndexBuffer();
	
	UINT			GetVertexStride() { return m_iVertexStride; }

	UINT			GetVerticesSize() { return m_iVerticesSize; }

	UINT			GetIndexCount() { return m_iIndexCount; }

	HRESULT			Bind(URenderer* renderer);

protected:
	 
	ComPtr<ID3D11Buffer> m_pVertexBuffer;
	ComPtr<ID3D11Buffer> m_pIndexBuffer;

	UINT			m_iVertexStride; // 객체 하나의 사이즈

	UINT			m_iVerticesSize;
	UINT			m_iIndexCount;

};


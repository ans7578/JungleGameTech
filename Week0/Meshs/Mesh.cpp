#include "Mesh.h"
#include "../Render/URenderer.h"


CMesh::CMesh(URenderer* renderer, void* pVertexData, UINT iVertexStride, UINT iVertexCount, UINT* pIndexData, UINT indexCount)
{
	m_pVertexBuffer = renderer->CreateVertexBuffer(pVertexData, iVertexStride * iVertexCount, D3D11_USAGE_IMMUTABLE);
	m_pIndexBuffer = renderer->CreateIndexBuffer(pIndexData, sizeof(UINT) * indexCount, D3D11_USAGE_IMMUTABLE);

	m_iVertexStride = iVertexStride;
	m_iIndexCount = indexCount;

}

CMesh::~CMesh()
{
	if (m_pVertexBuffer != nullptr)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}

	if (m_pIndexBuffer != nullptr)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}

}

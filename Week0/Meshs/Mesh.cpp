#include "Mesh.h"
#include "../Render/URenderer.h"


CMesh::CMesh(URenderer* renderer, FVertexSimple* vertices, UINT verticesSize, UINT* indices, UINT indexCount)
{
	m_pVertexBuffer = renderer->CreateVertexBuffer(vertices, verticesSize, D3D11_USAGE_IMMUTABLE);
	m_pIndexBuffer = renderer->CreateIndexBuffer(indices, sizeof(UINT) * indexCount, D3D11_USAGE_IMMUTABLE);

	m_iVertexStride = verticesSize / sizeof(FVertexSimple);
	m_iVerticesSize = verticesSize;
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

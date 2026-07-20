#include "Mesh.h"
#include "../Render/URenderer.h"


CMesh::CMesh(URenderer* renderer, void* pVertexData, UINT iVertexStride, UINT iVertexCount, UINT* pIndexData, UINT indexCount)
{
	renderer->CreateVertexBuffer(pVertexData, iVertexStride * iVertexCount, D3D11_USAGE_IMMUTABLE, m_pVertexBuffer.GetAddressOf());
	renderer->CreateIndexBuffer(pIndexData, sizeof(UINT) * indexCount, D3D11_USAGE_IMMUTABLE, m_pIndexBuffer.GetAddressOf());

	m_iVertexStride = iVertexStride;
	m_iIndexCount = indexCount;

}

CMesh::~CMesh()
{

}

ID3D11Buffer* CMesh::GetVertexBuffer()
{
	return m_pVertexBuffer.Get();
}

ID3D11Buffer* CMesh::GetIndexBuffer()
{
	return m_pIndexBuffer.Get();
}

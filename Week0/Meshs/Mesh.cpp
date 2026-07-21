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

HRESULT CMesh::Bind(URenderer* renderer)
{
	if (renderer == nullptr)
	{
		return E_FAIL;
	}

	UINT offset = 0; //정점 버퍼의 시작 오프셋
	renderer->DeviceContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &m_iVertexStride, &offset); //정점 버퍼 설정
	renderer->DeviceContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0); //인덱스 버퍼 설정

	return S_OK;
}

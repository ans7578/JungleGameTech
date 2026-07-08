#include "Actor.h"


AActor::AActor(URenderer* renderer, FVertexSimple* fVertices, UINT iVerticesData, UINT* iIndices, UINT iIndicesData)
{
	
	m_pVertexBuffer = renderer->CreateVertexBuffer(fVertices, iVerticesData, D3D11_USAGE_DYNAMIC , "ActorVertexBuffer");
	m_pIndexBuffer = renderer->CreateIndexBuffer(iIndices, iIndicesData, D3D11_USAGE_DYNAMIC,"ActorIndexBuffer");

	m_iIndicesCount = iIndicesData / sizeof(UINT);

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//좌표를  NDC 영역(-1~1) 으로 변환
	m_vPosition.x = ((float)(rand() % 160) + 20.f) * 0.01f - 1.f;
	m_vPosition.y = ((float)(rand() % 160) + 20.f) * 0.01f - 1.f;

	m_vVelocity.x = ((float)(rand() % 100 - 50)) * 0.001f;
	m_vVelocity.y = ((float)(rand() % 100 - 50)) * 0.001f;

}

AActor::~AActor()
{
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}
	if (m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}
}

void AActor::Update()
{
	m_vPosition += m_vVelocity;
}

void AActor::SetBuffer(URenderer* renderer, FVertexSimple* fVertices, UINT iVerticesData, UINT* iIndices, UINT iIndicesData)
{
	if (renderer == nullptr)
		return;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	renderer->DeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	{
		memcpy(mappedResource.pData, fVertices, iVerticesData);
	}
	renderer->DeviceContext->Unmap(m_pVertexBuffer, 0);

	renderer->DeviceContext->Map(m_pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	{
		memcpy(mappedResource.pData, iIndices, iIndicesData);
	}
	renderer->DeviceContext->Unmap(m_pIndexBuffer, 0);

}

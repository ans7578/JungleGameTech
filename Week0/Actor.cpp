#include "Actor.h"


AActor::AActor(URenderer* renderer, FVertexSimple* fVertices, UINT iVerticesData, UINT* iIndices, UINT iIndicesData)
{
	SetBuffer(renderer, fVertices, iVerticesData, iIndices, iIndicesData);

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

void AActor::SetBuffer(URenderer* Renderer, FVertexSimple* fVertices, UINT iVerticesData, UINT* iIndices, UINT iIndicesData)
{
	if (Renderer == nullptr)
		return;

	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
	}
	if (m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
	}

	m_pVertexBuffer = Renderer->CreateVertexBuffer(fVertices, iVerticesData);
	m_pIndexBuffer = Renderer->CreateIndexBuffer(iIndices, iIndicesData);

	m_iIndicesCount = iIndicesData / sizeof(UINT);
}

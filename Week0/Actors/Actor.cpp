#include "Actor.h"
#include "../Managers/ResourceManager.h"
#include "../Render/URenderer.h"
#include "../Meshs/Mesh.h"

UINT AActor::m_iRefCount = 0;

AActor::AActor()
{	
	m_iRefCount++;
}

AActor::~AActor()
{
	m_iRefCount--;
}

void AActor::Update()
{
	
}

void AActor::LateUpdate()
{
	m_fCBuffer.Color = m_fColor;
	m_fCBuffer.Offset = m_fPosition;
	m_fCBuffer.Size = m_fSize;
}

void AActor::Render(URenderer* renderer)
{
	renderer->UpdateConstantBuffer(&m_fCBuffer);
}

void AActor::SetMesh(EMeshType eMeshType)
{
	m_pMesh = CResourceManager::GetInstance().GetMesh(eMeshType);
}

void AActor::SetVelocity(float fVelocity)
{
	m_fVelocity.SetVector(fVelocity);
}

void AActor::SetSize(float scala)
{
	m_fSize.SetVector(scala);
}

void AActor::SetColor(float color)
{
	m_fColor.SetColor(color, color, color, 1.f);
}

void AActor::SetColor(const FColor& color)
{
	m_fColor = color;
}

URenderer::FConstantBuffer& const AActor::GetConstantBuffer()
{
	return m_fCBuffer;
}


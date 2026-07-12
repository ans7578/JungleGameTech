#include "Actor.h"
#include "../Managers/ResourceManager.h"
#include "../Render/URenderer.h"
#include "../Meshs/Mesh.h"

UINT AActor::m_iRefCount = 0;

AActor::AActor()
{	
	m_iRefCount++;

	AddComponent<UTransformComponent>(new UTransformComponent());
}

AActor::~AActor()
{
	m_iRefCount--;

	for (const auto& component : m_Components)
	{
		component->Release_Component();

		delete component;
	}
	m_Components.clear();
}

void AActor::Init()
{
	for (const auto& component : m_Components)
	{
		component->Init_Component();
	}
}

void AActor::Update()
{
	for (const auto& component : m_Components)
	{
		component->Update_Component();
	}
}

void AActor::LateUpdate()
{
	for (const auto& component : m_Components)
	{
		component->LateUpdate_Component();
	}
}

void AActor::RenderDebug()
{
	for (const auto& component : m_Components)
	{
		component->RenderDebug_Component();
	}
}

void AActor::Release()
{
	
}

void AActor::Render(URenderer* renderer)
{
	//DX행렬로 있던걸 수학적 행렬식으로 전치함.

	XMMATRIX matSRT = GetTransform()->GetSRTMatrix();

	m_fCBufferData.World = XMMatrixTranspose(matSRT);
	m_fCBufferData.Color = GetColor();

	renderer->UpdateConstantBuffer(&m_fCBufferData,sizeof(m_fCBufferData),URenderer::ECBufferType::CBUFFER_WORLD);
}

void AActor::SetMesh(EMeshType eMeshType)
{
	m_pMesh = CResourceManager::GetInstance().GetMesh(eMeshType);
}

void AActor::SetColor(float color)
{
	m_fColor.SetColor(color, color, color, 1.f);
}

void AActor::SetColor(const FColor& color)
{
	m_fColor = color;
}

UTransformComponent* const AActor::GetTransform()
{
	return GetComponent<UTransformComponent>();
}

template<typename T>
T* AActor::GetComponent()
{
	for (UComponentBase* component : m_Components)
	{
		T* targetComponent = dynamic_cast<T*>(component);

		if (targetComponent != nullptr)
		{
			return targetComponent;
		}
	}

	return nullptr;
}

template<typename T>
void AActor::AddComponent(T* pComponent)
{
	m_Components.push_back(pComponent);
}



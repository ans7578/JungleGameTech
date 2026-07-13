#include "Actor.h"
#include "../Managers/ResourceManager.h"
#include "../Render/URenderer.h"
#include "../Meshs/Mesh.h"
#include "../Components/TransformComponent.h"

UINT AActor::m_iRefCount = 0;

AActor::AActor()
{	
	m_iRefCount++;

	AddComponent(new UTransformComponent());
}

AActor::~AActor()
{
	m_iRefCount--;
}

void AActor::Init()
{
	for (UComponentBase* component : m_components)
	{
		component->Init_Component();
	}
}

void AActor::Update()
{
	for (UComponentBase* component : m_components)
	{
		component->Update_Component();
	}
}

void AActor::LateUpdate()
{
	for (UComponentBase* component : m_components)
	{
		component->LateUpdate_Component();
	}

	m_fCBuffer.World = GetTransform()->GetWorldMatrix();
	m_fCBuffer.Color = m_fColor;

}

void AActor::RenderDebug()
{
	for (UComponentBase* component : m_components)
	{
		component->RenderDebug_Component();
	}
}

void AActor::Render(URenderer* renderer)
{
	for (UComponentBase* component : m_components)
	{
		component->Render_Component(renderer);
	}

	renderer->UpdateConstantBuffer(&m_fCBuffer);
	renderer->RenderPrimitiveIndexed(GetMesh()->GetVertexBuffer(), GetMesh()->GetIndexBuffer(), GetMesh()->GetVertexStride(), GetMesh()->GetIndexCount());


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

URenderer::FConstantBuffer& const AActor::GetConstantBuffer()
{
	return m_fCBuffer;
}

UTransformComponent* AActor::GetTransform()
{
	return GetComponent<UTransformComponent>();
}

template<typename T>
void AActor::AddComponent(T* component)
{
	m_components.push_back(component);
}

template<typename T>
T* AActor::GetComponent()
{
	for (UComponentBase* component : m_components)
	{
		T* targetComponent = dynamic_cast<T*>(component);

		if (targetComponent != nullptr)
		{
			return targetComponent;
		}

	}
	return nullptr;
}

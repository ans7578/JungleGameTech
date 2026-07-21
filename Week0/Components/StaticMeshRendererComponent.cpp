#include "StaticMeshRendererComponent.h"

UStaticMeshRendererComponent::UStaticMeshRendererComponent()
{
}

UStaticMeshRendererComponent::~UStaticMeshRendererComponent()
{
}

void UStaticMeshRendererComponent::Init_Component()
{
}

void UStaticMeshRendererComponent::Update_Component()
{
}

void UStaticMeshRendererComponent::LateUpdate_Component()
{
}

void UStaticMeshRendererComponent::RenderDebug_Component()
{
}

void UStaticMeshRendererComponent::Render_Component(URenderer* renderer)
{
}

void UStaticMeshRendererComponent::Release_Component()
{
}

const char* UStaticMeshRendererComponent::GetComponentName()
{
    return nullptr;
}

void UStaticMeshRendererComponent::Bind(URenderer* renderer)
{
    m_pMesh.lock()->Bind(renderer);
    
    

    for (weak_ptr<UMaterialBase> elem : m_vecMaterials)
    {
        elem.lock()->Bind(renderer);
    }
}

HRESULT UStaticMeshRendererComponent::SetMesh(weak_ptr<CMesh> pMesh)
{
    if (pMesh.expired())
    {
        return E_FAIL;
	}

	m_pMesh = pMesh;

    return S_OK;
}

HRESULT UStaticMeshRendererComponent::AddMaterial(weak_ptr<UMaterialBase> pMaterial)
{
    if (pMaterial.expired())
    {
        return E_FAIL;
    }

	m_vecMaterials.push_back(pMaterial);

    return S_OK;
}

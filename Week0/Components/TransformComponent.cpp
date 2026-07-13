#include "TransformComponent.h"

UTransformComponent::UTransformComponent()
{
    m_fPosition = XMFLOAT3(0.f, 0.f, 0.f);
    m_fRotation = XMFLOAT3(0.f, 0.f, 0.f);
    m_fScale = XMFLOAT3(1.f, 1.f, 1.f);

    m_matTranslation = XMMatrixIdentity();
    m_matRotation = XMMatrixIdentity();
    m_matScale = XMMatrixIdentity();
}

UTransformComponent::~UTransformComponent()
{

}

void UTransformComponent::Init_Component()
{
}

void UTransformComponent::Update_Component()
{

}

void UTransformComponent::LateUpdate_Component()
{
    m_matScale = XMMatrixScaling(m_fScale.x, m_fScale.y, m_fScale.z);
    m_matTranslation = XMMatrixTranslation(m_fPosition.x, m_fPosition.y, m_fPosition.z);

    m_matRotation = XMMatrixRotationRollPitchYaw(m_fRotation.x, m_fRotation.y, m_fRotation.z);
    
 
    m_matWorld = m_matScale * m_matRotation * m_matTranslation;
}

void UTransformComponent::RenderDebug_Component()
{
}

void UTransformComponent::Render_Component(URenderer* renderer)
{
}

const char* UTransformComponent::GetComponentName()
{
    return "TransformComponent";
}

void UTransformComponent::Translation(const XMFLOAT3& vector)
{
    m_fPosition.x += vector.x;
    m_fPosition.y += vector.y;
    m_fPosition.z += vector.z;

}

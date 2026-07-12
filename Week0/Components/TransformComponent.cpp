#include "TransformComponent.h"

UTransformComponent::UTransformComponent()
{
	m_fPosition = XMFLOAT3(0.f, 0.f, 0.f);
	m_fScale	= XMFLOAT3(1.f, 1.f, 1.f);
	m_fRotation = XMFLOAT3(0.f, 0.f, 0.f);

	m_matScale = XMMatrixIdentity();
	m_matRoation = XMMatrixIdentity();
	m_matTranslation= XMMatrixIdentity();

	m_matSRT = XMMatrixIdentity();

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

	
	XMFLOAT3 angleToRadians = XMFLOAT3
	(
		XMConvertToRadians(m_fRotation.x),
		XMConvertToRadians(m_fRotation.y),
		XMConvertToRadians(m_fRotation.z)
	);

	XMVECTOR quaternion	= XMQuaternionRotationRollPitchYaw(angleToRadians.x, angleToRadians.y, angleToRadians.z);

	m_matRoation = XMMatrixRotationQuaternion(quaternion);

	m_matSRT = m_matScale * m_matRoation * m_matTranslation;
}

void UTransformComponent::RenderDebug_Component()
{
	ImGui::Text(GetComponentName());

	
	float position[3] = { m_fPosition.x, m_fPosition.y, m_fPosition.z };
	float rotation[3] = { m_fRotation.x, m_fRotation.y, m_fRotation.z };
	float scale[3] = { m_fScale.x, m_fScale.y, m_fScale.z };


	if (ImGui::InputFloat3("Position", position))
	{
		memcpy(&m_fPosition, position, sizeof(float) * 3);
	}
	if (ImGui::InputFloat3("Rotation", rotation))
	{
		memcpy(&m_fRotation, rotation, sizeof(float) * 3);
	}
	if (ImGui::InputFloat3("Scale", scale))
	{
		memcpy(&m_fScale, scale, sizeof(float) * 3);
	}
}

void UTransformComponent::Render_Component(URenderer* renderer)
{
	
}

void UTransformComponent::Release_Component()
{
}

void UTransformComponent::Translation(const XMFLOAT3& position)
{
	m_fPosition.x += position.x;
	m_fPosition.y += position.y;
	m_fPosition.z += position.z;
}

const char* UTransformComponent::GetComponentName()
{
	return "Transform";
}



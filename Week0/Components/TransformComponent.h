#pragma once
#include "../Headers.h"
#include "ComponentBase.h"


class UTransformComponent : public UComponentBase
{
public:
	UTransformComponent();
	virtual ~UTransformComponent();


public:
	// UComponentBase을(를) 통해 상속됨
	virtual void Init_Component() override;
	
	virtual void Update_Component() override;
	
	virtual void LateUpdate_Component() override;
	
	virtual void RenderDebug_Component() override;
	
	virtual void Render_Component(URenderer* renderer) override;
	
	virtual const char* GetComponentName() override;

public:
	const XMFLOAT3& GetScale() { return m_fScale; }
	const XMFLOAT3& GetRotation() { return m_fRotation; }
	const XMFLOAT3& GetPosition() { return m_fPosition; }

	const XMMATRIX& GetWorldMatrix() { return m_matWorld; }

	void	SetScale(const XMFLOAT3& scale) { memcpy(&m_fScale, &scale, sizeof(XMFLOAT3)); }
	void	SetRotation(const XMFLOAT3& roation) { memcpy(&m_fRotation, &roation, sizeof(XMFLOAT3)); }
	void	SetPosition(const XMFLOAT3& position) { memcpy(&m_fPosition, &position, sizeof(XMFLOAT3)); }

	void	Translation(const XMFLOAT3& vector);

	

private:
	XMFLOAT3	m_fScale;
	XMFLOAT3	m_fRotation;
	XMFLOAT3	m_fPosition;

	XMMATRIX	m_matScale;
	XMMATRIX	m_matRotation;
	XMMATRIX	m_matTranslation;

	XMMATRIX	m_matWorld; //  스케일 회전 이동이 모두 곱해진 행렬
};


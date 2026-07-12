#pragma once
#include "ComponentBase.h"
#include "../Headers.h"

class URenderer;

class UTransformComponent :
    public UComponentBase
{
public:
    UTransformComponent();
    virtual ~UTransformComponent();

    // UComponentBase을(를) 통해 상속됨
    void Init_Component() override;
    
    void Update_Component() override;
    
    void LateUpdate_Component() override;

    void RenderDebug_Component() override;

    void Render_Component(URenderer* renderer) override;

    void Release_Component() override;

    const char* GetComponentName() override;

    const XMMATRIX& GetSRTMatrix() { return m_matSRT; }

    const XMFLOAT3  GetPosition() { return m_fPosition; }
    const XMFLOAT3  GetScale() { return m_fScale; }
    const XMFLOAT3  GetRoation() { return m_fRotation; }

    void            SetPosition(const XMFLOAT3& position);
    void            SetRotation(const XMFLOAT3& rotation);
    void            SetScale(const XMFLOAT3& scale);
    void            Translation(const XMFLOAT3& position);

private:
    void        UpdateMatrix();

private:
    XMFLOAT3    m_fPosition;
    XMFLOAT3    m_fRotation;
    XMFLOAT3    m_fScale;


    XMMATRIX    m_matScale;
    XMMATRIX    m_matRoation;
    XMMATRIX    m_matTranslation;

    XMMATRIX    m_matSRT;

    bool        m_bChangedData = true;


};


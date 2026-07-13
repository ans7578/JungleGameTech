#pragma once
#include "../Actor.h"
class ACameraActor :
    public AActor
{
public:
    ACameraActor();
    virtual ~ACameraActor();
public:
    // AActor을(를) 통해 상속됨
    virtual const char* GetName() override;

    virtual void Update() override;

    virtual void LateUpdate() override;

    virtual void Render(URenderer* renderer) override;

private:
    URenderer::FCameraBufferData m_fCameraBufferData;

    float m_moveSpeed;

    float m_nearZ = 1.f;
    float m_farZ = 1000.f;
};


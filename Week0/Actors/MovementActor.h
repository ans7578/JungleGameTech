#pragma once
#include "Actor.h"

class AMovementActor :
    public AActor
{
public:
    AMovementActor();
    virtual ~AMovementActor();


public:
    virtual void Update() override;


    virtual void RenderDebug() override;

private:
    float m_moveAmount = 0.f;

    int m_iCallCount = 0;

    // AActor을(를) 통해 상속됨
    virtual const char* GetName() override;
};


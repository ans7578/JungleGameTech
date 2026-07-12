#pragma once
#include "Actor.h"
class ABoundActor :
    public AActor
{
public:
    ABoundActor();

    virtual ~ABoundActor();


public:
    virtual void Update() override;


    // AActor을(를) 통해 상속됨
    virtual const char* GetName() override;

    const XMFLOAT3& GetVelocity() { return m_fVelocity; }

    void            SetVelocity(const XMFLOAT3& velocity) { m_fVelocity = velocity; }
private:
    XMFLOAT3 m_fVelocity;
};


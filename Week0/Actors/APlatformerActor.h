#pragma once
#include "Actor.h"
class APlatformerActor : public AActor
{

public:
	APlatformerActor();
	virtual ~APlatformerActor();
public:
	// AActor을(를) 통해 상속됨
	const XMFLOAT3& GetVelocity() { return m_fVelocity; }

	void            SetVelocity(const XMFLOAT3& velocity) { m_fVelocity = velocity; }
	
	virtual const char* GetName() override;

	virtual void Update() override;

private:
	float		m_gravity;


private:
	XMFLOAT3    m_fVelocity;
	
};


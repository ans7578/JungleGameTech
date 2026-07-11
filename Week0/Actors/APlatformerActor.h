#pragma once
#include "Actor.h"
class APlatformerActor : public AActor
{

public:
	APlatformerActor();
	virtual ~APlatformerActor();
public:
	// AActor을(를) 통해 상속됨
	virtual const char* GetName() override;

	virtual void Update() override;

private:
	float m_gravity;

};


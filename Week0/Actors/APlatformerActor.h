#pragma once
#include "Actor.h"
class APlatformerActor : public AActor
{

public:
	APlatformerActor();
	~APlatformerActor();
public:
	// AActor을(를) 통해 상속됨
	const char* GetName() override;


	virtual void Update() override;

private:
	float m_gravity;

};


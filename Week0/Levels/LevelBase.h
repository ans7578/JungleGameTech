#pragma once
#include "../Headers.h"
#include  "../Actors/Actor.h"
#include "../Render/URenderer.h"

class CLevelBase 
{
public:
	CLevelBase();
	virtual ~CLevelBase();

public:
	virtual void Init_Level();

	virtual void Update_Level() = 0;

	virtual void LateUpdate_Level();

	virtual void Render_Level(URenderer* renderer);

	virtual void Render_Debug();

	virtual void Release_Level();

protected:
	std::vector<AActor*>	m_vecActors;
};


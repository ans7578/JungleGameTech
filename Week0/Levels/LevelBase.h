#pragma once
#include "../Headers.h"

class AActor;

class CLevelBase 
{
public:
	CLevelBase();
	virtual ~CLevelBase();

public:
	virtual void Init_Level() = 0;

	virtual void Update_Level() = 0;

	virtual void Render_Level() = 0;

	virtual void Release_Level() = 0;

protected:
	std::vector<AActor*>	m_vecActors;
};


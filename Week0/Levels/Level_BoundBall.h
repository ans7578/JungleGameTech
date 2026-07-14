#pragma once
#include "LevelBase.h"


class URenderer;

class CLevel_BoundBall : public CLevelBase
{
public:
	CLevel_BoundBall();
	virtual ~CLevel_BoundBall();

	// CLevelBase을(를) 통해 상속됨
public:
	virtual void Init_Level() override;
	
	virtual void Update_Level() override;
	
	virtual void Render_Level(URenderer* renderer) override;
	
	virtual void Release_Level() override;


	// CLevelBase을(를) 통해 상속됨
	virtual void RenderDebug_Level() override;


private:
	const float leftBorder = 0.f;
	const float rightBorder = 1000.f;
	const float topBorder = 1000.f;
	const float bottomBorder = 0.f;
};

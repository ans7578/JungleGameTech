#pragma once
#include "LevelBase.h"


class URenderer;

class CLevel_BoundBall : public CLevelBase
{
	// CLevelBase을(를) 통해 상속됨
public:
	virtual void Init_Level() override;
	
	virtual void Update_Level() override;
	
	virtual void Render_Level(URenderer* renderer) override;
	
	virtual void Release_Level() override;


	// CLevelBase을(를) 통해 상속됨
	virtual void Render_Debug() override;


private:
	const float leftBorder = -1.0f;
	const float rightBorder = 1.0f;
	const float topBorder = 1.0f;
	const float bottomBorder = -1.0f;
	const float sphereRadius = 1.0f;
};

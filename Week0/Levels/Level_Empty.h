#pragma once
#include "LevelBase.h"
class CLevel_Empty : public CLevelBase
{
public:
	CLevel_Empty() = default;
	virtual ~CLevel_Empty() =  default;

	// CLevelBase을(를) 통해 상속됨
	void Update_Level() override;
};


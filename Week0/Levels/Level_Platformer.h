#pragma once
#include "LevelBase.h"
class CLevel_Platformer :
    public CLevelBase
{
public:
    CLevel_Platformer();
    virtual ~CLevel_Platformer();

    // CLevelBase을(를) 통해 상속됨
    virtual void Init_Level() override;
    
    virtual void Update_Level() override;

    virtual void LateUpdate_Level() override;

    virtual void Render_Level(URenderer* renderer) override;
};


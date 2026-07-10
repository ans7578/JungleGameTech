#pragma once
#include "LevelBase.h"

class AActor;


class CLevel_MovementActor :
    public CLevelBase
{
    // CLevelBase을(를) 통해 상속됨
    virtual void Init_Level() override;
    virtual void Update_Level() override;
    virtual void Render_Level(URenderer* renderer) override;
    virtual void Render_Debug() override;
    virtual void Release_Level() override;


private:
    float m_LeftBorder = -1.f;
    float m_RightBorder = 1.f;
    float m_TopBorder = 1.f;
    float m_BottomBorder = -1.f;
};


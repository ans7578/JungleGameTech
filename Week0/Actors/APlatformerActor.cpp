#include "APlatformerActor.h"
#include "../Managers/InputManager.h"

APlatformerActor::APlatformerActor()
{
    m_gravity = -0.98f;

    SetSize(0.1f);
}

APlatformerActor::~APlatformerActor()
{

}

const char* APlatformerActor::GetName()
{
    return "APlatformerActor";
}

void APlatformerActor::Update()
{
    __super::Update();

    if (m_fPosition.y > 100.f)
    {
        m_fVelocity.y += m_gravity;
    }

    if (CInputManager::GetInstance().GetKeyUp(VK_SPACE))
    {
        m_fPosition.y += 350.f;
    }
    if (CInputManager::GetInstance().GetKey(VK_LEFT))
    {
        m_fPosition.x -= 50.f;
    }
    if (CInputManager::GetInstance().GetKey(VK_RIGHT))
    {
        m_fPosition.x += 50.f;
    }
    m_fPosition += m_fVelocity;
}

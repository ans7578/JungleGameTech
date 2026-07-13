#include "APlatformerActor.h"
#include "../Managers/InputManager.h"

APlatformerActor::APlatformerActor()
{
    m_gravity = -0.98f;

    GetTransform()->SetScale(XMFLOAT3(0.1f, 0.1f, 0.1f));
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

    XMFLOAT3 position = GetTransform()->GetPosition();

    if (position.y > 100.f)
    {
        m_fVelocity.y += m_gravity;
    }

    if (CInputManager::GetInstance().GetKeyUp(VK_SPACE))
    {
        position.y += 350.f;
    }
    if (CInputManager::GetInstance().GetKey(VK_LEFT))
    {
        position.x -= 50.f;
    }
    if (CInputManager::GetInstance().GetKey(VK_RIGHT))
    {
        position.x += 50.f;
    }
    GetTransform()->SetPosition(position);
    GetTransform()->Translation(m_fVelocity);
}

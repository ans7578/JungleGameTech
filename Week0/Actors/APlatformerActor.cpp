#include "APlatformerActor.h"
#include "../Managers/InputManager.h"

APlatformerActor::APlatformerActor()
{
    m_gravity = -0.98f;

    m_fVelocity = XMFLOAT3(0.f, 0.f, 0.f);

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

    if (GetTransform()->GetPosition().y > 100.f)
    {
        m_fVelocity.y += m_gravity;
    }

    if (CInputManager::GetInstance().GetKeyUp(VK_SPACE))
    {
        GetTransform()->Translation(XMFLOAT3(0, 350.f, 0.f));
    }
    if (CInputManager::GetInstance().GetKey(VK_LEFT))
    {
        GetTransform()->Translation(XMFLOAT3(-50.f, 0.f, 0.f));
    }
    if (CInputManager::GetInstance().GetKey(VK_RIGHT))
    {
        GetTransform()->Translation(XMFLOAT3(50.f, 0.f, 0.f));
    }
    GetTransform()->Translation(m_fVelocity);
}

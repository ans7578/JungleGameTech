#include "CameraActor.h"
#include "../../Headers.h"
#include "../../Managers/InputManager.h"

ACameraActor::ACameraActor()
{
    m_moveSpeed = 0.05f;

    m_eActorType = ACTOR_CAMERA;

}

ACameraActor::~ACameraActor()
{

}

const char* ACameraActor::GetName()
{
    return "CameraActor";
}

void ACameraActor::Update()
{
    __super::Update();

    if (CInputManager::GetInstance().GetKey('A'))
    {
        GetTransform()->Translation(XMFLOAT3(-m_moveSpeed, 0.f, 0.f));
    }
    if (CInputManager::GetInstance().GetKey('D'))
    {
        GetTransform()->Translation(XMFLOAT3(m_moveSpeed, 0.f, 0.f));
    }
    if (CInputManager::GetInstance().GetKey('W'))
    {
        GetTransform()->Translation(XMFLOAT3(0.f, m_moveSpeed, 0.f));
    }
    if (CInputManager::GetInstance().GetKey('S'))
    {
        GetTransform()->Translation(XMFLOAT3(0, -m_moveSpeed, 0.f));
    }
}

void ACameraActor::LateUpdate()
{
    __super::LateUpdate();
}

void ACameraActor::Render(URenderer* renderer)
{
    FXMMATRIX world = GetTransform()->GetSRTMatrix();

    XMVECTOR  determinant =   DirectX::XMMatrixDeterminant(world);

    XMMATRIX invView = XMMatrixInverse(&determinant, world);

    m_fCameraBufferData.View = XMMatrixTranspose(invView);
    
    XMMATRIX projectionMatrix = XMMatrixOrthographicLH
    (
        (float)renderer->ViewportInfo.Width,
        (float)renderer->ViewportInfo.Height,
        m_nearZ,
        m_farZ
        );

    m_fCameraBufferData.Projection = XMMatrixTranspose(projectionMatrix);

    renderer->UpdateConstantBuffer(&m_fCameraBufferData, sizeof(m_fCameraBufferData), URenderer::CBUFFER_CAMERA);
    renderer->SetConstantBuffer(URenderer::CBUFFER_CAMERA);
}

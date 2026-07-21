#include "MovementActor.h"
#include "../Managers/InputManager.h"
#include "../Components/StaticMeshRendererComponent.h"
#include "../Managers/ResourceManager.h"
#include "../Materials/Material_Unlit_Standard.h"

AMovementActor::AMovementActor()
{
	m_moveAmount = 0.1f;

	m_eActorType = ACTOR_PLAYER;

	
	GetTransform()->SetScale(XMFLOAT3(100.f, 100.f, 100.f));

	AddComponent<UStaticMeshRendererComponent>(new UStaticMeshRendererComponent());



}

AMovementActor::~AMovementActor()
{
}

void AMovementActor::Init()
{
	__super::Init();

	weak_ptr<CMesh> mesh = CResourceManager::GetInstance().LoadMesh(L"Mesh_Rect");

	weak_ptr<UMaterialBase> matUnlitStandard = CResourceManager::GetInstance().LoadMaterial(L"Unlit_Standard");


	GetComponent<UStaticMeshRendererComponent>()->SetMesh(mesh);
	GetComponent<UStaticMeshRendererComponent>()->AddMaterial(matUnlitStandard);
}

void AMovementActor::Update()
{

	if (CInputManager::GetInstance().GetKey(VK_UP))
	{
		GetTransform()->Translation(XMFLOAT3(0.f, m_moveAmount, 0.f));
		m_iCallCount++;
	}

	if (CInputManager::GetInstance().GetKey(VK_DOWN))
	{
		GetTransform()->Translation(XMFLOAT3(0.f, -m_moveAmount, 0.f));
	}

	if (CInputManager::GetInstance().GetKey(VK_RIGHT))
	{
		GetTransform()->Translation(XMFLOAT3(m_moveAmount, 0.f, 0.f));
	}

	if (CInputManager::GetInstance().GetKey(VK_LEFT))
	{
		GetTransform()->Translation(XMFLOAT3(-m_moveAmount, 0.f, 0.f));
	}
}

void AMovementActor::RenderDebug()
{
	__super::RenderDebug();
	ImGui::Text("Call Count : %d", m_iCallCount);
}

void AMovementActor::Render(URenderer* renderer)
{
	__super::Render(renderer);

	UStaticMeshRendererComponent* meshRenderer = GetComponent<UStaticMeshRendererComponent>();

	meshRenderer->Bind(renderer);

	renderer->RenderPrimitiveIndexed(meshRenderer->GetMesh().lock()->GetIndexCount());

}

const char* AMovementActor::GetName()
{
	if (m_strName.empty())
	{
		m_strName = "AMovementActor" + std::to_string(m_iRefCount);
	}

	return m_strName.c_str();
}

	#pragma once
#include "./ComponentBase.h"
#include "../Meshs/Mesh.h"
#include "../Materials/MaterialBase.h"
#include "../Enums.h"



class UStaticMeshRendererComponent : public UComponentBase
{
public:
	UStaticMeshRendererComponent();
	virtual ~UStaticMeshRendererComponent();

	// UComponentBase을(를) 통해 상속됨
	void Init_Component() override;
	
	void Update_Component() override;
	
	void LateUpdate_Component() override;

	void RenderDebug_Component() override;
	
	void Render_Component(URenderer* renderer) override;
	
	void Release_Component() override;
	
	const char* GetComponentName() override;
	
	void	Bind(URenderer* renderer);

	HRESULT SetMesh(weak_ptr<CMesh> pMesh);

	HRESULT AddMaterial(weak_ptr<UMaterialBase> pMaterial);

	weak_ptr<CMesh> GetMesh() { return m_pMesh; }

	weak_ptr<UMaterialBase> GetMaterial(int iIndex) { return m_vecMaterials[iIndex]; }




private:
	weak_ptr<CMesh> m_pMesh;
	vector<weak_ptr<UMaterialBase>> m_vecMaterials;
};


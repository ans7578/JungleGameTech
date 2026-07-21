#pragma once
#include "MaterialBase.h"
class UMaterial_Unlit_Standard:
    public UMaterialBase
{
public:
    UMaterial_Unlit_Standard();
    virtual ~UMaterial_Unlit_Standard();
public:
    virtual HRESULT Init() override;

    void Bind(URenderer* render) override;
    const wchar_t* GetMaterialName() override;
};


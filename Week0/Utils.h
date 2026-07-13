#pragma once


#include <DirectXMath.h>

using namespace DirectX;

namespace Utils
{
    XMFLOAT2 ConvertScreenToNDC(float screenX, float screenY, float screenWidth, float screenHeight)
    {
        XMFLOAT2 ndc;

        //스크린 좌표를 ndc좌표로 변환한다
        ndc.x = (2.0f * screenX) / screenWidth - 1.0f;
        ndc.y = (2.0f * screenY) / screenHeight - 1.0f;

        return ndc;       
    }

    const XMFLOAT3& XMFloatIdentity()
    {
        return XMFLOAT3(0.f, 0.f, 0.f);
    }

}
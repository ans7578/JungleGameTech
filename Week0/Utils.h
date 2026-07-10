#pragma once

#include "Headers.h"
#include <DirectXMath.h>


using namespace DirectX;

namespace Utils
{
    XMFLOAT2 ConvertScreenToNDC(float screenX, float screenY, float screenWidth, float screenHeight)
    {
        XMFLOAT2 ndc;

        // 수식을 코드로 그대로 이식한다.
        ndc.x = (2.0f * screenX) / screenWidth - 1.0f;
        ndc.y = (2.0f * screenY) / screenHeight - 1.0f;

        return ndc;
    }
}


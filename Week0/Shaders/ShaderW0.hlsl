//ShaderW0.hlsl

/*
cbuffer constBuffer : register(b0)
{
    float3  Offset; //정점 위치를 이동시키기 위한 오프셋 값
    float   Pad;
    
    float3  Size;
    float   Pad2;
    
    float4  Color;
};
*/

cbuffer constBuffer : register(b1)
{
    matrix World;
    float4 Color;
};



struct VS_INPUT
{
    float4 position : POSITION; //버텍스 버퍼로부터 정점 위치를 받아온다
};

// 정점 셰이더에서 픽셀 셰이더로 전달할 구조체
struct PS_INPUT
{
    float4 position : SV_POSITION; //픽셀 셰이더에 전달하기 위해 변환된 위치값
    float4 color : COLOR; //픽셀 셰이더에 전달하기 위해 변환된 색상값
};


PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;
    
    output.position = mul(input.position, World);
    output.color = Color; //정점 색상을 그대로 전달
    
    return output;
    
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    return input.color; //픽셀 셰이더에서 색상을 그대로 출력
}
//ShaderW0.hlsl


cbuffer constBuffer : register(b0)
{
    float3 Offset; //정점 위치를 이동시키기 위한 오프셋 값
    float Pad;
    float3 Scale; //정점 크기를 조절하기 위한 스케일 값
    float Pad2;
    float3 Color;
    float Pad3;
};

struct VS_INPUT
{
    float4 Pos : POSITION; //버텍스 버퍼로부터 정점 위치를 받아온다
    float4 Color : COLOR; //버텍스 버퍼로부터 정점 색상을 받아온다
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
    
    output.position = input.Pos * float4(Scale, 1.f) + float4(Offset, 0); //정점 위치를 그대로 전달
    output.color = input.Color * float4(Color, 0); //정점 색상을 그대로 전달
    
    return output;
    
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    return input.color; //픽셀 셰이더에서 색상을 그대로 출력
}
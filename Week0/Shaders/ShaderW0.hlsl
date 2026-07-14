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
cbuffer cameraBuffer : register(b0) 
{
    matrix View;
    matrix Projection;
}

cbuffer constBuffer : register(b1)
{
    matrix World;
    float4 Color;
};

Texture2D   texture0 : register(t0);

SamplerState sampler0 : register(s0);

struct VS_INPUT
{
    float3 position : POSITION; //버텍스 버퍼로부터 정점 위치를 받아온다
    float2 uv : TEXCOORD0;
};

// 정점 셰이더에서 픽셀 셰이더로 전달할 구조체
struct PS_INPUT
{
    float4 position : SV_POSITION; //픽셀 셰이더에 전달하기 위해 변환된 위치값
    float2 uv: TEXCOORD; //픽셀 셰이더에 전달하기 위해 변환된 색상값
    float4 color : COLOR;
};


PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;
    
    float4 position = float4(input.position, 1.f);

    output.position = mul(position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    

    output.uv = input.uv;

    output.color = Color;

    return output;
    
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    // 샘플링 전에 UV가 0~1 범위를 벗어나는지 디버깅용으로 체크할 수 있네.
    // float4 texColor = texture0.Sample(sampler0, input.uv);

    // 만약 텍스처 출력이 안 된다면, 아래와 같이 UV를 출력해서 좌표가 넘어오는지 확인하게.
    float4 finalColor = texture0.Sample(sampler0, input.uv);
    finalColor.rgb *= input.color.rgb;

    return finalColor;
    //return input.color;
     
}
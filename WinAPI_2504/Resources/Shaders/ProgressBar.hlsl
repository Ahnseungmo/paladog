cbuffer WorldBuffer : register(b0)
{
    matrix world;
}
cbuffer ViewBuffer : register(b1)
{
    matrix view;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

struct Input
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct Output
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

Output VS(Input input)
{
    Output output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;
    
    return output;
}

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

Texture2D baseMap : register(t0);
SamplerState samplerState : register(s0);

cbuffer ProgressBarBuffer : register(b1)
{
    float amount;
}

float4 PS(Output output) : SV_TARGET
{
    float4 baseColor = baseMap.Sample(samplerState, output.uv);
    
    float2 dir = output.uv - float2(0.5, 0.5);
    float PI = 3.141592;
    
    float angle = atan2(dir.y, dir.x) + PI / 2;
    angle = fmod(angle + 2 * PI, 2 * PI);

    if (angle > amount)
        baseColor.a = 0.0f;
    
    return baseColor * color;
}
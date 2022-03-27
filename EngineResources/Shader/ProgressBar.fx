#include "CbufferHeader.fx"

cbuffer ProgressBarCBuffer : register(b1)
{
    float Percent;
    int PregressDirect;
    float2 Empty2;
};

struct VertexIn
{
    float4 Position : POSITION;
    float4 Texcoord : TEXTURECOORD;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float4 Texcoord : TEXTURECOORD;
};

VertexOut ProgressBar_VS(VertexIn _in)
{
    VertexOut output = (VertexOut)0;

    float4 Pos = _in.Position;

	// 오른쪽 -> 왼쪽
    if (PregressDirect == 0)
    {
        if (Pos.x == 1.f)
        {
            Pos.x = Percent;
        }
    }
	// 왼쪽 -> 오른쪽
    if (PregressDirect == 1)
    {
        if (Pos.x == 0.f)
        {
            Pos.x = 1.f - Percent;
        }
    }
	// 위 -> 아래
    if (PregressDirect == 2)
    {
        if (Pos.y == 1.f)
        {
            Pos.y = Percent;
        }
    }
	// 아래 -> 위
    if (PregressDirect == 3)
    {
        if (Pos.y == 0.f)
        {
            Pos.y = 1.f - Percent;
        }
    }

    output.Position.w = 1.0f;
    output.Position = mul(Pos, WVP);

    float4 Texcoord = _in.Texcoord;

	// 오른쪽 -> 왼쪽
    if (PregressDirect == 0)
    {
        if (Texcoord.x == 1.f)
        {
            Texcoord.x = Percent;
        }
    }
	// 왼쪽 -> 오른쪽
    if (PregressDirect == 1)
    {
        if (Texcoord.x == 0.f)
        {
            Texcoord.x = 1.f - Percent;
        }
    }
	// 위 -> 아래
    if (PregressDirect == 2)
    {
        if (Texcoord.y == 0.f)
        {
            Texcoord.y = 1.f - Percent;
        }
    }
	// 아래 -> 위
    if (PregressDirect == 3)
    {
        if (Texcoord.y == 1.f)
        {
            Texcoord.y = Percent;
        }
    }

    output.Texcoord = Texcoord;

    return output;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

// UI ProgressBar Shader Function(Pixel Shader)
float4 ProgressBar_PS(VertexOut _in) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _in.Texcoord.xy);

    return Color;
}

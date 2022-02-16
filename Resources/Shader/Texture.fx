#include "CbufferHeader.fx"

float4 Texture_VS(float4 pos : POSITION) : SV_POSITION
{
    pos = mul(pos, WorldWorld_);

    return pos;
}

float4 Texture_PS(float4 pos : SV_POSITION) : SV_Target0
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}



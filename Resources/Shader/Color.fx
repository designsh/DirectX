
//float4x4 World;
//float4x4 View;
//float4x4 Proj;

float4 Color_VS(float4 pos : POSITION) : SV_POSITION
{
    // pos *= World * View * Proj;

    return pos;
}


float4 Color_PS(float4 pos : SV_POSITION) : SV_Target0
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}

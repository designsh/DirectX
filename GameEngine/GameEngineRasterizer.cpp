#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() :
	ViewPort_{}
{
}

GameEngineRasterizer::~GameEngineRasterizer()
{
}

GameEngineRasterizer::GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept :
	ViewPort_(_other.ViewPort_)
{
}

void GameEngineRasterizer::RasterizerUpdate(float4& _Pos)
{
	// 각 정점(벡터)의 x,y,z값을 월드행렬*뷰행렬 곱에 의해 생성된 본래의 z값을 이용하여 모든 원소를 나누어
	// 비율을 계산한다.
	// 원근투영행렬에서 본래의 z값을 w에 저장하고있으므로 x,y,z를 w값으로 나누어 -1 ~ 1사이의 비율을 계산한다.
	_Pos.x /= _Pos.w;
	_Pos.y /= _Pos.w;
	_Pos.z /= _Pos.w;
	_Pos.w = 1.f;

	// 2차원 평면의 크기로 전환(화면상의 크기로)






}


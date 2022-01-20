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
	//_Pos* ViewPort_;
}


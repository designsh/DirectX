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
	// �� ����(����)�� x,y,z���� �������*����� ���� ���� ������ ������ z���� �̿��Ͽ� ��� ���Ҹ� ������
	// ������ ����Ѵ�.
	// ����������Ŀ��� ������ z���� w�� �����ϰ������Ƿ� x,y,z�� w������ ������ -1 ~ 1������ ������ ����Ѵ�.
	_Pos.x /= _Pos.w;
	_Pos.y /= _Pos.w;
	_Pos.z /= _Pos.w;
	_Pos.w = 1.f;

	// 2���� ����� ũ��� ��ȯ(ȭ����� ũ���)






}


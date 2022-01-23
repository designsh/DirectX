#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	float4x4 ViewPort_;

public:
	GameEngineRasterizer(); // default constructer ����Ʈ ������
	~GameEngineRasterizer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void RasterizerUpdate(float4& _Pos);

public:
	void SetViewPort(float _ScreenX, float _ScreenY, float _StartX, float _StartY, float _MinZ, float _MaxZ)
	{
		ViewPort_.ViewPortCenter(_ScreenX, _ScreenY, _StartX, _StartY, _MinZ, _MaxZ);
	}
};


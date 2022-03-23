#pragma once
#include "GameEngineDevice.h"
#include <ThirdParty/Include/FW1Font/FW1FontWrapper.h>

// �з� : ��Ʈ
// �뵵 : 
// ���� : TEXT�� ȭ�鿡 �������ϴ� ����� ����
class GameEngineFontManager;
class GameEngineFont : public GameEngineObjectNameBase
{
	friend class GameEngineFontManager;

private:
	static IFW1Factory* FontFactory_;

private:	// member Var
	IFW1FontWrapper* FontWrapper_;

public:
	GameEngineFont();
	~GameEngineFont();

protected:		// delete constructer
	GameEngineFont(const GameEngineFont& _other) = delete;
	GameEngineFont(GameEngineFont&& _other) noexcept = delete;

private:		//delete operator
	GameEngineFont& operator=(const GameEngineFont& _other) = delete;
	GameEngineFont& operator=(const GameEngineFont&& _other) = delete;

protected:
	void Load(const std::string& _FontFileName);

public:
	void DrawFont(const std::string& _Text, float _Size, const float4& _Pos, const float4& _PivotPos = float4::ZERO, const float4& _Color = float4::WHITE, unsigned int _Flags = FW1_CENTER);
};


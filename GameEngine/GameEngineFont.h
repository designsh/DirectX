#pragma once
#include "GameEngineDevice.h"
#include <ThirdParty/Include/FW1Font/FW1FontWrapper.h>

// 분류 : 폰트
// 용도 : 
// 설명 : TEXT를 화면에 렌더링하는 기능을 제공
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


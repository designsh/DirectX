#pragma once
#include "GameEngineDevice.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTexture;
class GameEngineRenderTarget : public GameEngineObjectNameBase
{
private:	// member Var
	std::vector<GameEngineTexture*> Textures_;
	std::vector<ID3D11RenderTargetView*> RenderTargetViews_;
	std::vector<float4> ClearColor_;

public:
	GameEngineRenderTarget(); // default constructer 디폴트 생성자
	~GameEngineRenderTarget(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRenderTarget(const GameEngineRenderTarget& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRenderTarget(GameEngineRenderTarget&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void Clear();
	void Setting(int _Index = -1);

public:
	void Create(const std::string _TextureName, float4 _ClearColor);
};


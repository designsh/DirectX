#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11RasterizerState*	State_;					// Rasterizer 상태
	D3D11_VIEWPORT			ViewPort_;			// Viewport의 치수를 정의
	D3D11_RECT						Scissor_;				// 가위-사각형 치수를 정의

private:
	bool										SicssorFlag_;		// 가위-사각형 지정 사용 Flag

public:
	GameEngineRasterizer(); // default constructer 디폴트 생성자
	~GameEngineRasterizer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SetViewPort(float _Width, float _Height, float _TopLeftX, float _TopLeftY, float _MinDepth, float _MaxDepth);
	void SetScissor(LONG _Left, LONG _Top, LONG _Right, LONG _Bottom);

public:
	void Create(const D3D11_RASTERIZER_DESC& _Value);

public:
	void SettingViewPort();

public:
	void SettingScissor();

public:
	void Setting();
};


#pragma once
#include "GameEngineDevice.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	// 사용자편의를 위해 두개의 상태(SOLID, WIREFRAME)를 만들어놓고 교체 가능
	ID3D11RasterizerState*		State_;								// 초기 : SOLD용 Rasterizer 상태
	ID3D11RasterizerState*		OldState_;						// 초기 : WIREFRAME용 Rasterizer 상태

private:
	D3D11_RASTERIZER_DESC Desc_;								// D3D11_RASTERIZER_DESC.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID 용 상태정의
	D3D11_RASTERIZER_DESC WireDesc_;						// D3D11_RASTERIZER_DESC.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME 용 상태정의

private:
	D3D11_VIEWPORT				ViewPort_;						// Viewport의 치수를 정의

private:
	std::vector<D3D11_RECT>	ScissorRects_;					// 가위-사각형 치수를 정의(여러개 셋팅이 가능하므로 벡터로 관리)
	int												ChangeScissorIndex_;	// 가위-사각형목록 중 현재 사용할 치수정의
	
public:
	GameEngineRasterizer(); // default constructer 디폴트 생성자
	~GameEngineRasterizer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public: // Solid <-> WireFrame Rasterizer State Change
	void SwitchState();

public: // ViewPort
	void SetViewPort(float _Width, float _Height, float _TopLeftX, float _TopLeftY, float _MinDepth, float _MaxDepth);

public: // Add Scissor & Current Scissor Change
	void PushScissorRect(D3D11_RECT _Rect);
	void ChangeScissorRect(int _Index);

public: // Rasterizer State 생성 및 클리어
	void Create(const D3D11_RASTERIZER_DESC& _Value);
	void Clear();

public:
	void SettingViewPort();

public:
	void SettingScissor();

public:
	void Setting();
};


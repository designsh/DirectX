#pragma once
#include "GameEngineShader.h"
#include "GameEngineDevice.h"

// 분류 : 픽셀(Pixel) 셰이더
// 용도 : 
// 설명 : 픽셀 셰이더는 렌더링 될 각각의 픽셀들의 색을 계산한다. 그러므로 픽셀 셰이더는 최종적으로 픽셀이 어떻게 보일지를 결정한다. 
//            픽셀 셰이더는 간단하게 언제나 같은 색을 출력하는 간단한 일에서부터, 텍스처로부터 색을 읽어오거나, 빛을 적용하는 것, 
//            범프 매핑, 그림자, 반사광, 투명처리 등 복잡한 현상 등을 수행할 수 있다.
class GameEnginePixelShader : public GameEngineShader
{
private:	// member Var
	ID3D11PixelShader*				Shader_;		// 

public:
	GameEnginePixelShader();
	~GameEnginePixelShader();

protected:		// delete constructer
	GameEnginePixelShader(const GameEnginePixelShader& _other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _other) noexcept = delete;

private:		//delete operator
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _other) = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader&& _other) = delete;

public: // Create Pixel Shader
	bool Create(const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Create Pixel Compile
	bool Compile();

public: // Create Pixel Setting
	void Setting();
};


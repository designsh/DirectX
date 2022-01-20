#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRasterizer
{
private:	// member Var
	float4x4 ViewPort_;

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
	void RasterizerUpdate(float4& _Pos);
};


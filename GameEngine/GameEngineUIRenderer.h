#pragma once
#include "GameEngineImageRenderer.h"

// 분류 : UI Renderer
// 용도 : 
// 설명 : 
class GameEngineTexture;
class GameEngineFolderTexture;
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineUIRenderer : public GameEngineImageRenderer
{
private:
	static GameEngineRenderTarget* FontTarget_;
	static int UIRendererCount;

private:	// member Var
	bool IsText_;
	std::string FontName_;
	std::string PrintText_;
	float FontSize_;
	float4 FontPivot_;
	float4 Color_;
	unsigned int Flags_;
	int MaxLen_;

private:
	float4 CuttingUV_;

public:
	GameEngineUIRenderer(); // default constructer 디폴트 생성자
	~GameEngineUIRenderer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineUIRenderer(const GameEngineUIRenderer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineUIRenderer(GameEngineUIRenderer&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	std::string GetPrintText() const
	{
		return PrintText_;
	}

	int GetPrintTextLen() const
	{
		return static_cast<int>(PrintText_.length());
	}

private:
	void Start() override;
	void Render() override;

public:
	void SetRenderGroup(int _Order) override;

public: // Text 관련
	void TextSetting(std::string _FontName, std::string _PrintText, float _FontSize, unsigned int _Flags = 0, float4 _Color = float4::WHITE, const float4& _FontPivot = float4::ZERO, int _MaxLen = 15);
	bool AddText(std::string _PrintText);
	bool DelText();
	void AllDelText();
	void SetPrintText(const std::string& _PrintText);
};


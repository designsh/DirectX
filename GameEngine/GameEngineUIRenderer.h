#pragma once
#include "GameEngineImageRenderer.h"

// �з� : UI Renderer
// �뵵 : 
// ���� : 
class GameEngineTexture;
class GameEngineFolderTexture;
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineUIRenderer : public GameEngineImageRenderer
{
private:	// member Var
	bool IsText_;
	std::string FontName_;
	std::string PrintText_;
	float FontSize_;
	float4 FontPivot_;
	float4 Color_;
	unsigned int Flags_;

public:
	GameEngineUIRenderer(); // default constructer ����Ʈ ������
	~GameEngineUIRenderer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineUIRenderer(const GameEngineUIRenderer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineUIRenderer(GameEngineUIRenderer&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Render() override;

public:
	void SetRenderGroup(int _Order) override;

public: // Text ����
	void TextSetting(std::string _FontName, std::string _PrintText, float _FontSize, unsigned int _Flags = 0, float4 _Color = float4::WHITE, const float4& _FontPivot = float4::ZERO);
	void AddText(std::string _PrintText);
	void DelText();
};


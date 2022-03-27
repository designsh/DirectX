#pragma once
#include "GameEngineImageRenderer.h"

#include "Enums.h"

struct ProgressBarCBuffer
{
	float Percent;
	int PregressDirect;
	float Empty1;
	float Empty2;

	ProgressBarCBuffer() : Percent(1.f), PregressDirect(0), Empty1(0.f), Empty2(0.f)
	{
	}
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTexture;
class GameEngineFolderTexture;
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineProgressBarRenderer : public GameEngineImageRenderer
{
private:	// member Var
	ProgressBarCBuffer ProgressBarData_;

private:
	float4 ColorTint_;

public:
	GameEngineProgressBarRenderer();
	~GameEngineProgressBarRenderer();

protected:		// delete constructer
	GameEngineProgressBarRenderer(const GameEngineProgressBarRenderer& _other) = delete;
	GameEngineProgressBarRenderer(GameEngineProgressBarRenderer&& _other) noexcept = delete;

private:		//delete operator
	GameEngineProgressBarRenderer& operator=(const GameEngineProgressBarRenderer& _other) = delete;
	GameEngineProgressBarRenderer& operator=(const GameEngineProgressBarRenderer&& _other) = delete;

private:
	void Start() override;
	void Render() override;

public:
	void SetRenderGroup(int _Order) override;

public:
	void SetProgressBarDirect(int _ProgressBarDir);
	void SetPercent(float _Percent);
	void SetColor(float4 _Color);
};


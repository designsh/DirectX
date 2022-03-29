#pragma once
#include "GameEngineGUI.h"
#include "GameEngineRenderTarget.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineImageShotWindow : public GameEngineGUIWindow
{
	struct RenderTargetDrawData
	{
	public:
		std::string Name;
		GameEngineRenderTarget* Target;
		float4 Size_;
		bool ScaleCheck;
	};

private:	// member Var
	ID3D11ShaderResourceView* View_;
	float4 Size_;
	std::vector<RenderTargetDrawData> DrawRenderTarget_;

public:
	GameEngineImageShotWindow();
	~GameEngineImageShotWindow();

protected:		// delete constructer
	GameEngineImageShotWindow(const GameEngineImageShotWindow& _other) = delete;
	GameEngineImageShotWindow(GameEngineImageShotWindow&& _other) noexcept = delete;

private:		//delete operator
	GameEngineImageShotWindow& operator=(const GameEngineImageShotWindow& _other) = delete;
	GameEngineImageShotWindow& operator=(const GameEngineImageShotWindow&& _other) = delete;

protected:
	void Start() override;
	void OnGUI() override;

public:
	void ClaerRenderTarget()
	{
		DrawRenderTarget_.clear();
	}

	void PushRenderTarget(std::string _Name, GameEngineRenderTarget* _RenderTarget, float4 Size_)
	{
		DrawRenderTarget_.push_back({ _Name, _RenderTarget, Size_, false });
	}

	void SetView(ID3D11ShaderResourceView* _View, float4 _Size)
	{
		Size_ = _Size;
		View_ = _View;
	}
};


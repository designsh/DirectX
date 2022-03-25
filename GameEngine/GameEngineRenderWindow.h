#pragma once
#include "GameEngineGUI.h"
#include "GameEngineRenderTarget.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRenderWindow : public GameEngineGUIWindow
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
	std::vector<RenderTargetDrawData> DrawRenderTarget_;

public:
	GameEngineRenderWindow();
	~GameEngineRenderWindow();

protected:		// delete constructer
	GameEngineRenderWindow(const GameEngineRenderWindow& _other) = delete;
	GameEngineRenderWindow(GameEngineRenderWindow&& _other) noexcept = delete;

private:		//delete operator
	GameEngineRenderWindow& operator=(const GameEngineRenderWindow& _other) = delete;
	GameEngineRenderWindow& operator=(const GameEngineRenderWindow&& _other) = delete;

protected:
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
};


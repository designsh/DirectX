#pragma once
#include "GameEngineGUI.h"
#include "GameEngineRenderTarget.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineLevelControlWindow : public GameEngineGUIWindow
{
private:	// member Var

public:
	GameEngineLevelControlWindow();
	~GameEngineLevelControlWindow();

protected:		// delete constructer
	GameEngineLevelControlWindow(const GameEngineLevelControlWindow& _other) = delete;
	GameEngineLevelControlWindow(GameEngineLevelControlWindow&& _other) noexcept = delete;

private:		//delete operator
	GameEngineLevelControlWindow& operator=(const GameEngineLevelControlWindow& _other) = delete;
	GameEngineLevelControlWindow& operator=(const GameEngineLevelControlWindow&& _other) = delete;

protected:
	void OnGUI() override;

public:
};


#pragma once
#include <GameEngine/GameEngineGUI.h>

// 분류 : 
// 용도 : 
// 설명 : 
class EditorModeSelectWindow : public GameEngineGUIWindow
{
private:	// member Var

public:
	EditorModeSelectWindow();
	~EditorModeSelectWindow();

protected:		// delete constructer
	EditorModeSelectWindow(const EditorModeSelectWindow& _other) = delete;
	EditorModeSelectWindow(EditorModeSelectWindow&& _other) noexcept = delete;

private:		//delete operator
	EditorModeSelectWindow& operator=(const EditorModeSelectWindow& _other) = delete;
	EditorModeSelectWindow& operator=(const EditorModeSelectWindow&& _other) = delete;

protected:
	virtual void OnGUI() override;

public:
};


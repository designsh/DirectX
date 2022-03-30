#pragma once
#include <GameEngine/GameEngineGUI.h>

// �з� : 
// �뵵 : 
// ���� : 
class EditorControlWindow : public GameEngineGUIWindow
{
public:	// member Var
	class IsoTileMap* Map;

public:
	EditorControlWindow();
	~EditorControlWindow();

protected:		// delete constructer
	EditorControlWindow(const EditorControlWindow& _other) = delete;
	EditorControlWindow(EditorControlWindow&& _other) noexcept = delete;

private:		//delete operator
	EditorControlWindow& operator=(const EditorControlWindow& _other) = delete;
	EditorControlWindow& operator=(const EditorControlWindow&& _other) = delete;

protected:
	virtual void OnGUI() override;

public:
	void GUIWindowOff();
};


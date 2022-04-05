#pragma once
#include <GameEngine/GameEngineGUI.h>

// 분류 : 
// 용도 : 
// 설명 : 
class CameraComponent;
class EditorControlWindow : public GameEngineGUIWindow
{
public:	// member Var
	class IsoTileMap* Map;
	float Zoom;
	float ZoomMin;
	float ZoomMax;

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
};


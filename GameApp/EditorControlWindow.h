#pragma once
#include <GameEngine/GameEngineGUI.h>

// 분류 : 
// 용도 : 
// 설명 : 

enum class TileType
{
	FLOOR,
	WALL
};

class CameraComponent;
class EditorControlWindow : public GameEngineGUIWindow
{
public:	// member Var
	class IsoTileMap* Map_;
	float Zoom_;
	float ZoomMin_;
	float ZoomMax_;

	TileType SelectMode_;
	int SelectTileIndex_;

private:
	int FloorXCount_;
	int FloorYCount_;
	int WallXCount_;
	int WallYCount_;

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


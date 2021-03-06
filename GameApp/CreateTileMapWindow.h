#pragma once
#include <GameEngine/GameEngineGUI.h>

// 타일 타입
enum class TileType
{
	FLOOR,
	WALL,
	OBJECT
};

// 분류 : 
// 용도 : 
// 설명 : 
class CameraComponent;
class EditorTileMap;
class CreateTileMapWindow : public GameEngineGUIWindow
{
public:
	EditorTileMap* TileMap_;

public:
	float Zoom_;
	float ZoomMin_;
	float ZoomMax_;

public:
	TileType SelectMode_;
	int SelectTileIndex_;

private:
	int FloorXCount_;
	int FloorYCount_;
	int WallXCount_;
	int WallYCount_;

private: // 저장 및 로드 관련
	char FileName_[256];

public:
	CreateTileMapWindow();
	~CreateTileMapWindow();

protected:		// delete constructer
	CreateTileMapWindow(const CreateTileMapWindow& _other) = delete;
	CreateTileMapWindow(CreateTileMapWindow&& _other) noexcept = delete;

private:		//delete operator
	CreateTileMapWindow& operator=(const CreateTileMapWindow& _other) = delete;
	CreateTileMapWindow& operator=(const CreateTileMapWindow&& _other) = delete;

protected:
	virtual void OnGUI() override;

public:
};


#pragma once
#include <GameEngine/GameEngineGUI.h>

// Ÿ�� Ÿ��
enum class TileType
{
	FLOOR,
	WALL
};

// �з� : 
// �뵵 : 
// ���� : 
class CameraComponent;
class TileMap;
class CreateTileMapWindow : public GameEngineGUIWindow
{
public:
	TileMap* TileMap_;

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


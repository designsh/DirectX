#pragma once
#include <GameEngine/GameEngineLevel.h>

enum class EditorMode
{
	None = -1,
	Fixed,
	Random,
};

// 분류 : 맵에디터 레벨
// 용도 : 
// 설명 : 
class EditorTileMap;
class EditorRandomMap;
class EditorModeSelectWindow;
class CreateTileMapWindow;
class CreateRandomMapWindow;
class MapEditorLevel : public GameEngineLevel
{
private:
	static bool ResourceLoadEndCheck;

public:
	static EditorMode CurEditorMode;

private:	// member Var
	EditorTileMap* EditorFixedMap_;
	EditorRandomMap* EditorRandomMap_;

private: // Window
	EditorModeSelectWindow* EditorModeSelWindow_;
	CreateTileMapWindow* TileMapWindow_;
	CreateRandomMapWindow* RandomMapWindow_;

private:
	float MoveSpeed_;

public:
	MapEditorLevel();
	~MapEditorLevel();

protected:		// delete constructer
	MapEditorLevel(const MapEditorLevel& _other) = delete;
	MapEditorLevel(MapEditorLevel&& _other) noexcept = delete;

private:		//delete operator
	MapEditorLevel& operator=(const MapEditorLevel& _other) = delete;
	MapEditorLevel& operator=(const MapEditorLevel&& _other) = delete;

private:
	void CreateLevelActor();

public:
	virtual void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	virtual void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;

private:
	void FixedMapControlMode();
	void RandomMapControlMode();
};


#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 맵에디터 레벨
// 용도 : 
// 설명 : 
class TileMap;
class MapEditorLevel : public GameEngineLevel
{
private:
	static bool ResourceLoadEndCheck;

private:	// member Var
	TileMap* TileMap_;

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
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};


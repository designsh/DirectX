#pragma once
#include <GameEngine/GameEngineActor.h>
#include "TileMap_Common.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTileMapRenderer;
class TownMap : public GameEngineActor
{
private:	// member Var
	MapType MapType_;

private: // 맵의 각 타입별(바닥,벽,오브젝트) 정보


private: // 해당 맵의 네비게이션 정보


public:
	TownMap();
	~TownMap();

protected:		// delete constructer
	TownMap(const TownMap& _other) = delete;
	TownMap(TownMap&& _other) noexcept = delete;

private:		//delete operator
	TownMap& operator=(const TownMap& _other) = delete;
	TownMap& operator=(const TownMap&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	bool TownLevel_FixedMapLoad();
};


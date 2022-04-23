#pragma once
#include <GameEngine/GameEngineActor.h>
#include "TileMap_Common.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTileMapRenderer;
class TownMap : public GameEngineActor
{
private:	// member Var
	MapType MapType_;

private: // ���� �� Ÿ�Ժ�(�ٴ�,��,������Ʈ) ����


private: // �ش� ���� �׺���̼� ����


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


#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine\GameEngineTextureManager.h>
#include <GameEngineBase\GameEngineRandom.h>

union TileIndex
{
public:
	struct 
	{
		int X_;
		int Y_;
	};

	__int64 Index_;

	TileIndex()
		: X_(0), Y_(0)
	{

	}

	TileIndex(int _X, int _Y) 
		: X_(_X), Y_(_Y)
	{

	}
};

// 분류 : 애니메이션
// 용도 : 타이틀레벨 로고
// 설명 : 
class GameEngineUIRenderer;
class IsoTileMap : public GameEngineActor
{
public:
	// constrcuter destructer
	IsoTileMap();
	~IsoTileMap();

	// delete Function
	IsoTileMap(const IsoTileMap& _Other) = delete;
	IsoTileMap(IsoTileMap&& _Other) noexcept = delete;
	IsoTileMap& operator=(const IsoTileMap& _Other) = delete;
	IsoTileMap& operator=(IsoTileMap&& _Other) noexcept = delete;

	void SetTile(float4 _Pos);
	void SetTile(TileIndex _Index);

	void DelTile(float4 _Pos);

	TileIndex GetIndex(float4 _Pos);

	float4 GetIsoPos(float4 _Pos);

	void SetFloorTileTexture(const std::string& _FloorTile)
	{
		FloorTile_ = _FloorTile;
	}

	GameEngineTexture* GetFloorTileTexture()
	{
		return GameEngineTextureManager::GetInst().Find(FloorTile_);
	}

	void SetSelectTileIndex(int _Index)
	{
		CurTileIndex_ = _Index;
	}

private:
	void Start() override;

	float4 TileSize;
	float4 TileSizeHalf;
	float4 IndexPivotPos;
	// 8 바이트
	std::unordered_map<__int64, class GameEngineImageRenderer*> Tiles_;

	std::string FloorTile_;
	int CurTileIndex_;

private:

	GameEngineRandom Random;
	float4 RandomStart;

public:
	void RandomRoad(int Count);

	void RandomRoad();


};


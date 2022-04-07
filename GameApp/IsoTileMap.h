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
class GameEngineTileMapRenderer;
class IsoTileMap : public GameEngineActor
{
private:
	static bool FirstRandomLoad_;
	static std::vector<int> IgnoreRange;
	static std::vector<std::vector<float4>> RandomRange;
	static std::vector<std::vector<int>> RandomReversRange;
	static std::vector<std::vector<int>> RandomNextRange;

private: 
	// 생성된 
	std::unordered_map<__int64, class GameEngineTileMapRenderer*> FloorTiles_;

	// 규칙이 다른거기 때문에
	std::unordered_map<__int64, class GameEngineTileMapRenderer*> WallTiles_;


private: // 바닥타일정보
	float4 FloorTileSize_;
	float4 FloorTileSizeHalf_;
	float4 FloorTileImageSize_;
	float4 FloorTileIndexPivotPos_;

private: // 벽타일정보
	float4 WallTileSize_;
	float4 WallTileSizeHalf_;
	float4 WallTileImageSize_;
	float4 WallTileIndexPivotPos_;


private: // 각각의 텍스쳐명
	std::string FloorTileTextureName_;
	std::string WallTileTextureName_;

private:
	GameEngineRandom Random_;
	std::vector<float4> RandomStartPos_;

public:
	IsoTileMap();
	~IsoTileMap();

protected:		// delete constructer
	IsoTileMap(const IsoTileMap& _Other) = delete;
	IsoTileMap(IsoTileMap&& _Other) noexcept = delete;

private:		//delete operator
	IsoTileMap& operator=(const IsoTileMap& _Other) = delete;
	IsoTileMap& operator=(IsoTileMap&& _Other) noexcept = delete;

public:
	inline void SetFloorTileTexture(const std::string& _FloorTileTextureName)
	{
		FloorTileTextureName_ = _FloorTileTextureName;
	}

	inline void SetWallTileTexture(const std::string& _WallTileTextureName)
	{
		WallTileTextureName_ = _WallTileTextureName;
	}

	inline GameEngineTexture* GetFloorTileTexture()
	{
		return GameEngineTextureManager::GetInst().Find(FloorTileTextureName_);
	}

	inline GameEngineTexture* GetWallTileTexture()
	{
		return GameEngineTextureManager::GetInst().Find(WallTileTextureName_);
	}

public:
	void SetFloorTile(float4 _Pos, int CurTileIndex_);
	void SetFloorTile(TileIndex _Index, int CurTileIndex_);

	void SetWallTile(float4 _Pos, int CurTileIndex_);
	void SetWallTile(TileIndex _Index, int CurTileIndex_);

	void DelFloorTile(float4 _Pos);
	void DelWallTile(float4 _Pos);
	void AllTileClear();

public:
	TileIndex GetIndex(float4 _Pos);
	float4 GetIsoPos(float4 _Pos);

private:
	void Start() override;

public: // Random TileMap
	void RandomRoad(int _Count, bool _Multidirectional = false);

public: // Save & Load
	void MapSave();
	void MapLoad();
};


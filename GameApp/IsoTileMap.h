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



// �з� : �ִϸ��̼�
// �뵵 : Ÿ��Ʋ���� �ΰ�
// ���� : 
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
	std::unordered_map<__int64, class GameEngineTileMapRenderer*> FloorTiles_;
	std::unordered_map<__int64, class GameEngineTileMapRenderer*> WallTiles_;

private:
	std::unordered_map<__int64, class GameEngineTileMapRenderer*> FloorGrides_;
	std::unordered_map<__int64, class GameEngineTileMapRenderer*> WallGrides_;

private: // Ÿ������
	float4 TileSize_;
	float4 TileSizeHalf_;
	float4 TileSizeHHalf_;
	float4 TileSizeHHHalf_;

private: // �ٴ�Ÿ������
	float4 FloorTileImageSizeHalf_;
	float4 FloorTileImageSize_;
	float4 FloorTileIndexPivotPos_;

private: // ��Ÿ������
	float4 WallTileImageSizeHalf_;
	float4 WallTileImageSize_;
	float4 WallTileIndexPivotPos_;
	float4 WallGridTileIndexPivotPos_;

private: // ������ �ؽ��ĸ�
	std::string FloorTileTextureName_;
	std::string WallTileTextureName_;

private:
	GameEngineRandom Random_;
	std::vector<float4> RandomStartPos_;

private:
	bool FloorGridMode_;
	bool WallGridMode_;
	bool FloorAllMode_;
	bool WallAllMode_;

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

	inline bool GetFloorGrideMode()
	{
		return FloorGridMode_;
	}

	inline bool GetWallGrideMode()
	{
		return WallGridMode_;
	}

	inline bool GetFloorAllMode()
	{
		return FloorAllMode_;
	}

	inline bool GetWallAllMode()
	{
		return WallAllMode_;
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
	TileIndex GetFloorTileIndex(float4 _Pos);
	TileIndex GetWallTileIndex(float4 _Pos);

public:
	float4 GetFloorIsoPos(float4 _Pos);
	float4 GetWallIsoPos(float4 _Pos);

private:
	void Start() override;

public: // Random TileMap
	void RandomRoad(int _Count, bool _Multidirectional = false);

public: // �׽�Ʈ�� Ÿ�� Ÿ�Ժ� �׸��� ����
	void CreateFloorGrid(int _X, int _Y);
	void ClearFloorGrid();
	void CreateWallGrid(int _X, int _Y);
	void ClearWallGrid();

public: // �׸����� ����
	void FloorGridModeSwitching();
	void WallGridModeSwitching();

	void FloorAllModeSwitching();
	void WallAllModeSwitching();

public: // Save & Load
	void MapSave();
	void MapLoad();
};


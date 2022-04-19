#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineTextureManager.h>

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

// 렌더링타입
enum class TileRenderingType
{
	ALL,		// 그리드+타일
	GRID,		// 그리드
	TILE		// 타일
};

// 벽타일 기본타입(방향구분)
enum class WallBasicType
{
	NONE,		// 벽정보는 존재하나, 렌더링하지않음
	RT,			// 우상단(좌하단)방향
	RB,			// 우하단(좌상단)방향
	BENT,		// 꺽이는벽
};

// 벽타일 상세타입(역할구분)
enum class WallDetailType
{
	NORMAL,		// 일반벽
	DOOR,		// 문
};

// 바닥타일 정보
struct FloorTileInfo
{
	// 바닥타일 정보

	// 인덱스정보
	int FloorIndexX;
	int FloorIndexY;
	int FloorImageIndex;
	
	// 렌더링 정보
	std::string FloorTextureName;
	float4 FloorTileSize;
	float4 FloorRenderSize;
	float4 FloorRenderPivotPos;
};

// 벽타일 정보
struct WallTileInfo
{
	// 벽타일 정보

	// 인덱스 및 타입정보
	int WallIndexX;
	int WallIndexY;
	int WallImageIndex;
	WallBasicType WallBasicType;
	WallDetailType WallDetailType;

	// 렌더링 정보
	std::string WallTextureName;
	float4 WallTileSize;
	float4 WallRenderSize;
	float4 WallRenderPivotPos;
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTileMapRenderer;
class TileMap : public GameEngineActor
{
#pragma region 실질적인 타일정보
private: // 실질적으로 저장되는 타일정보(값형)
	std::vector<std::vector<FloorTileInfo>> FloorTileInfo_;
	std::vector<std::vector<WallTileInfo>> WallTileInfo_;
#pragma endregion

#pragma region 에디터용도
private: // 텍스쳐 명칭
	std::string FloorTileTextureName_;
	std::string WallTileTextureName_;

private: // 에디터 화면 렌더링 용도
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallTiles_;

	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorGrides_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallGrides_;

private: // 타일정보
	float4 TileSize_;
	float4 TileSizeHalf_;
	float4 TileSizeHHalf_;
	float4 TileSizeHHHalf_;

private: // 바닥타일정보
	float4 FloorTileImageSizeHalf_;
	float4 FloorTileImageSize_;
	float4 FloorTileIndexPivotPos_;

private: // 벽타일정보
	float4 WallTileImageSizeHalf_;
	float4 WallTileImageSize_;
	float4 WallTileIndexPivotPos_;
	float4 WallGridTileIndexPivotPos_;

private: // 렌더링모드
	TileRenderingType TileRenderingType_;

#pragma endregion

public:
	TileMap();
	~TileMap();

protected:		// delete constructer
	TileMap(const TileMap& _other) = delete;
	TileMap(TileMap&& _other) noexcept = delete;

private:		//delete operator
	TileMap& operator=(const TileMap& _other) = delete;
	TileMap& operator=(const TileMap&& _other) = delete;

private:
	void Start() override;

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

public: // 렌더링모드 선택
	void SetTileRenderingMode(TileRenderingType _RenderingType);

public: // IMGUI Window 표시용
	float4 GetFloorIsoPos(float4 _Pos);
	float4 GetWallIsoPos(float4 _Pos);

public: // GetTileIndex
	TileIndex GetFloorTileIndex(float4 _Pos);
	TileIndex GetWallTileIndex(float4 _Pos);

public: // SetTile/DelTile
	void SetFloorTile(float4 _Pos, int CurTileIndex_);
	void SetFloorTile(TileIndex _Index, int CurTileIndex_);
	void SetWallTile(float4 _Pos, int CurTileIndex_);
	void SetWallTile(TileIndex _Index, int CurTileIndex_);
	void DelFloorTile(float4 _Pos);
	void DelWallTile(float4 _Pos);

public: // CreateAutoMap Mode
	// 타일정보 생성 : 각 조건에 맞게 처리되며 정보생성이 완료되면, 그리드형태로 화면에 렌더링한다.
	void CreateFloorTileInfo(int _WidthTileCount, int _HeightTileCount);
	void CreateWallTileInfo(); // 벽타일의 갯수는 바닥타일 갯수에 비례하여 생성된다.

	// 생성된 정보를 이용하여 특정 조건에 해당하는 타일을 제외한 모든 타일은 디폴트타일로 정보갱신
	void UpdateFloorTileInfo(int _DefaultTileIndex);
	void UpdateWallTileInfo(int _DefaultTileIndex);

	// 현재 생성한 모든 타일정보 및 렌더링 정보 삭제
	//void AutoModeTileAllClear();

public:
	void AllClear();

	void AllClearFloorTile();
	void AllClearFloorTileInfo();
	void AllClearFloorTileMapRenderer();

	void AllClearWallTile();
	void AllClearWallTileInfo();
	void AllClearWallTileMapRenderer();
};


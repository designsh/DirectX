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
	NONE,		// 벽으로판단하나, 렌더링없음
	NORMAL,		// 벽으로판단하지않고, 렌더링없음

	// RT_T
	RT_T,			// 우상단(좌하단)방향(연속된벽) - 중심기준(0,0) 윗벽
	RT_T_RE,		// 우상단방향으로 윗벽의 끝(BENT와 연결되는 벽)
	RT_T_LE,		// 좌하단방향으로 윗벽의 끝(BENT직전에 RT가 끝)

	// RT_B
	RT_B,			// 우상단(좌하단)방향(연속된벽) - 중심기준(0,0) 아랫벽
	RT_B_RE,		// 우상단방향으로 아랫벽의 끝(BENT가 끝)
	RT_B_LE,		// 좌하단방향으로 아랫벽의 끝(BENT직전에 RT가 끝)

	// RB_L
	RB_L,			// 우하단(좌상단)방향(연속된벽) - 중심기준(0,0) 왼쪽벽
	RB_L_BE,		// 우하단방향으로 왼쪽벽의 끝(BENT직전에 RB가 끝)
	RB_L_TE,		// 좌상단방향으로 왼쪽벽의 끝(BENT가 끝)

	// RB_R
	RB_R,			// 우하단(좌상단)방향(연속된벽) - 중심기준(0,0) 오른쪽벽
	RB_R_BE,		// 우하단방향으로 오른쪽벽의 끝(BENT직전에 RB가 끝)
	RB_R_TE,		// 좌상단방향으로 오른쪽벽의 끝(BENT와 연결되는 벽)

	// BENT
	BENT_MULTI,		// 꺽이는벽(렌더러를 2개 가진다) - 중심기준(0,0) 우상단꺽이는벽 => RT_T_RE와 RB_R_TE가 만나려고하는 벽(멀티렌더러)
	BENT_SINGLE,	// 꺽이는벽(렌더러를 1개 가진다) - 중심기준(0,0) 좌하단꺽이는벽 => RT_B_LE와 RB_L_BE가 만나려고하는 벽(단독렌더러)
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

class GameEngineTileMapRenderer;
struct WallTileRender
{
	GameEngineTileMapRenderer* Tiles1_;
	GameEngineTileMapRenderer* Tiles2_;
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


	std::unordered_map<__int64, WallTileRender> WallTiles_;

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

#pragma region 특별조건벽타일이미지인덱스
	// RT_T
	int Wall_RT_T_ImageIndex_;
	int Wall_RT_T_LE_ImageIndex_;
	int Wall_RT_T_RE_ImageIndex_;

	// RT_B
	int Wall_RT_B_ImageIndex_;
	int Wall_RT_B_LE_ImageIndex_;
	int Wall_RT_B_RE_ImageIndex_;

	// RB_L
	int Wall_RB_L_ImageIndex_;
	int Wall_RB_L_TE_ImageIndex_;
	int Wall_RB_L_BE_ImageIndex_;

	// RB_R
	int Wall_RB_R_ImageIndex_;
	int Wall_RB_R_TE_ImageIndex_;
	int Wall_RB_R_BE_ImageIndex_;

	// BENT_SINGLE
	int Wall_BENT_SINGLE_ImageIndex_;

	// BENT_MULTI1
	int Wall_BENT_MULTI1_ImageIndex_;

	// BENT_MULTI2
	int Wall_BENT_MULTI2_ImageIndex_;
#pragma endregion

#pragma region 그리드On/Off상태값
	bool FloorGridesActive_;
	bool WallGridesActive_;
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
	void FloorGridesSwitching();
	void WallGridesSwitching();

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
	void CreateFloorTileInfo(int _WidthTileCount, int _HeightTileCount, int _ImageIndex);
	void CreateWallTileInfo(); // 벽타일의 갯수는 바닥타일 갯수에 비례하여 생성된다.

	// 생성된 바닥타일 정보를 이용하여 특정 조건에 해당하는 타일을 제외한 모든 타일은 디폴트타일로 정보갱신
	void UpdateFloorTileInfo();

	// 생성된 바닥타일 정보를 이용하여 특정 조건에 해당하는 타일을 제외한 모든 타일은 디폴트타일로 정보갱신
	// 1. 각 ACT별 조건별 이미지정보 매칭
	void SetTownWallTexture();
	void SetCatacombsWallTexture();
	void SetChaosSanctuaryWallTexture();

	// 2. 1.에서 지정된 타일로 현재 텍스쳐 매칭 후 정보 갱신
	void UpdateWallTileInfo();
	
	

	

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


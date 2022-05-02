#pragma once
#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineTextureManager.h>
#include "TileMap_Common.h"

// 바닥타일 렌더링타입
enum class FloorRenderingType
{
	TILE,		// 타일모드
	GRID		// 그리드모드
};

// 벽타일 렌더링타입
enum class WallRenderingType
{
	TILE1,				// 타일모드(타일1렌더러 교체)
	TILE2,				// 타일모드(타일2렌더러 교체)
	GRID_NOR,			// 그리드(벽이 아니면서 렌더링안하는 타입)
	GRID_NONE,			// 그리드(벽이면서 렌더링안하는 타입)
	GRID_RT_T,			// 그리드모드(RT_T)
	GRID_RT_T_LE,		// 그리드모드(RT_T_LE)
	GRID_RT_T_RE,		// 그리드모드(RT_T_RE)
	GRID_RT_B,			// 그리드모드(RT_B)
	GRID_RT_B_LE,		// 그리드모드(RT_B_LE)
	GRID_RT_B_RE,		// 그리드모드(RT_B_RE)
	GRID_RB_L,			// 그리드모드(RB_L)
	GRID_RB_L_TE,		// 그리드모드(RB_L_TE)
	GRID_RB_L_BE,		// 그리드모드(RB_L_BE)
	GRID_RB_R,			// 그리드모드(RB_R)
	GRID_RB_R_TE,		// 그리드모드(RB_R_TE)
	GRID_RB_R_BE,		// 그리드모드(RB_R_BE)
	GRID_BENT_SINGLE,	// 그리드모드(BENT_SINGLE)
	GRID_BENT_MULTI1,	// 그리드모드(BENT_MULTI1)
	GRID_BENT_MULTI2,	// 그리드모드(BENT_MULTI2)
};

// 오브젝트타일 렌더링타입(벽으로 취급)
enum class ObjectRenderingType
{
	TILE,				// 단순 타일(이미지인덱스에 영향)
	GRID_WALL,			// 벽타일의 NONE타입과 동일(오브젝트 기본타입에 영향)
	GRID_NORMAL,		// 아무것도 렌더링하지않은 타일(오브젝트 기본타입에 영향)
	GRID_OBJECT,		// 오브젝트가 렌더링되어있는 타일(오브젝트 기본타입에 영향)
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
class EditorTileMap : public GameEngineActor
{
#pragma region 실질적인 타일정보
private: // 실질적으로 저장되는 타일정보(값형)
	std::vector<std::vector<FloorTileInfo>> FloorTileInfo_;
	std::vector<std::vector<WallTileInfo>> WallTileInfo_;
	std::vector<std::vector<ObjectTileInfo>> ObjectTileInfo_;
#pragma endregion

#pragma region 에디터용도
private: // 텍스쳐 명칭
	std::string FloorTileTextureName_;
	std::string WallTileTextureName_;
	std::string ObjectTileTextureName_;

private: // 에디터 화면 렌더링 용도
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;
	std::unordered_map<__int64, WallTileRender> WallTiles_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> ObjectTiles_;

	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorGrides_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallGrides_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> ObjectGrides_;

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

private: // 오브젝트타일정보
	float4 ObjectTileImageSizeHalf_;
	float4 ObjectTileImageSize_;
	float4 ObjectTileIndexPivotPos_;

private: // 렌더링모드
	FloorRenderingType FloorRenderingType_;
	WallRenderingType WallRenderingType_;
	ObjectRenderingType ObjectRenderingType_;

#pragma endregion

#pragma region 벽타일 특별조건 이미지인덱스
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
	bool ObjectGridesActive_;
#pragma endregion

public:
	EditorTileMap();
	~EditorTileMap();

protected:		// delete constructer
	EditorTileMap(const EditorTileMap& _other) = delete;
	EditorTileMap(EditorTileMap&& _other) noexcept = delete;

private:		//delete operator
	EditorTileMap& operator=(const EditorTileMap& _other) = delete;
	EditorTileMap& operator=(const EditorTileMap&& _other) = delete;

private:
	void Start() override;

public:
	void FloorGridesSwitching();
	void WallGridesSwitching();
	void ObjectGridesSwitching();

public:
	inline void SetFloorTileTexture(const std::string& _FloorTileTextureName)
	{
		FloorTileTextureName_ = _FloorTileTextureName;
	}

	inline void SetWallTileTexture(const std::string& _WallTileTextureName)
	{
		WallTileTextureName_ = _WallTileTextureName;
	}

	inline void SetObjectTileTexture(const std::string& _ObjectTileTextureName)
	{
		ObjectTileTextureName_ = _ObjectTileTextureName;
	}

	inline GameEngineTexture* GetFloorTileTexture()
	{
		return GameEngineTextureManager::GetInst().Find(FloorTileTextureName_);
	}

	inline GameEngineTexture* GetWallTileTexture()
	{
		return GameEngineTextureManager::GetInst().Find(WallTileTextureName_);
	}

	inline GameEngineTexture* GetObjectTileTexture()
	{
		return GameEngineTextureManager::GetInst().Find(ObjectTileTextureName_);
	}

public: // 렌더링모드 선택
	void SetFloorRenderingMode(FloorRenderingType _FloorRenderingType);
	void SetWallRenderingMode(WallRenderingType _WallRenderingType);
	void SetObjectRenderingMode(ObjectRenderingType _ObjectRenderingType);

public: // 현재 렌더링모드 Get
	inline FloorRenderingType GetCurFloorRenderType()
	{
		return FloorRenderingType_;
	}

	inline WallRenderingType GetCurWallRenderType()
	{
		return WallRenderingType_;
	}

	inline ObjectRenderingType GetCurObjectRenderType()
	{
		return ObjectRenderingType_;
	}

public: // IMGUI Window 표시용
	float4 GetFloorIsoPos(float4 _Pos);
	float4 GetWallIsoPos(float4 _Pos);
	float4 GetObjectIsoPos(float4 _Pos);

public: // GetTileIndex
	TileIndex GetFloorTileIndex(float4 _Pos);
	TileIndex GetWallTileIndex(float4 _Pos);
	TileIndex GetObjectTileIndex(float4 _Pos);

public: // SetTile/DelTile
	void SetFloorTile(float4 _Pos, int CurTileIndex_);
	void SetFloorTile(TileIndex _Index, int CurTileIndex_);
	void SetWallTile(float4 _Pos, int CurTileIndex_);
	void SetWallTile(TileIndex _Index, int CurTileIndex_);
	void SetObjectTile(float4 _Pos, int CurTileIndex_);
	void SetObjectTile(TileIndex _Index, int CurTileIndex_);
	void DelFloorTile(float4 _Pos);
	void DelWallTile(float4 _Pos);
	void DelObjectTile(float4 _Pos);

public: // SetGrid/DelGrid
	void SetFloorGird(float4 _Pos, int CurTileIndex_);
	void SetFloorGird(TileIndex _Index, int CurTileIndex_);
	void SetWallGird(float4 _Pos, int CurTileIndex_);
	void SetWallGird(TileIndex _Index, int CurTileIndex_);
	void SetObjectGird(float4 _Pos, int CurTileIndex_);
	void SetObjectGird(TileIndex _Index, int CurTileIndex_);
	void DelFloorGird(float4 _Pos);
	void DelWallGird(float4 _Pos);
	void DelObjectGird(float4 _Pos);

public: // CreateAutoMap Mode
	// 타일정보 생성 : 각 조건에 맞게 처리되며 정보생성이 완료되면, 그리드형태로 화면에 렌더링한다.
	void CreateFloorTileInfo(int _WidthTileCount, int _HeightTileCount, int _ImageIndex);	// 인자로 수신한 너비/높이 인덱스를 이용하여 바닥타일 정보 및 그리드 생성
	void CreateWallTileInfo();																// 벽타일의 갯수는 바닥타일 갯수에 비례하여 생성
	void CreateObjectTileInfo();															// 벽타일생성이 완료된 후 호출되어 오브젝트 배치를 위한 정보생성시작

	// 생성된 바닥타일 정보를 이용하여 특정 조건에 해당하는 타일을 제외한 모든 타일은 디폴트타일로 정보갱신
	void UpdateFloorTileInfo();

	// 생성된 바닥타일 정보를 이용하여 특정 조건에 해당하는 타일을 제외한 모든 타일은 디폴트타일로 정보갱신
	// 1. 각 ACT별 조건별 이미지정보 매칭
	void SetTownWallTexture();
	void SetCatacombsWallTexture();
	void SetChaosSanctuaryWallTexture();

	// 2. 1.에서 지정된 타일로 현재 텍스쳐 매칭 후 정보 갱신
	void UpdateWallTileInfo();
	
	// 현재 자동생성한 모든 타일정보 및 렌더링 정보 삭제
	void AutoModeTileAllClear();

public:
	void AllClear();

	void AllClearFloorTile();
	void AllClearFloorTileInfo();
	void AllClearFloorTileMapRenderer();

	void AllClearWallTile();
	void AllClearWallTileInfo();
	void AllClearWallTileMapRenderer();

	void AllClearObjectTile();
	void AllClearObjectTileInfo();
	void AllClearObjectTileMapRenderer();

public:
	// 맵파일 저장
	void MapFileSave();

	// 맵파일로드 후 타일, 그리드 생성
	void MapFileLoad();
	void CreatedAfterLoading();
	void CreatedAfterLoading_FloorGrides();
	void CreatedAfterLoading_WallGrides();
	void CreatedAfterLoading_ObjectGrides();
	void CreatedAfterLoading_FloorTiles();
	void CreatedAfterLoading_WallTiles();
	void CreatedAfterLoading_ObjectTiles();
};


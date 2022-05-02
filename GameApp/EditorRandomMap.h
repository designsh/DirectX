#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>

#include "RandomTileMap_Common.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTileMapRenderer;
class EditorRandomMap : public GameEngineActor
{
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

private:



public:
	EditorRandomMap();
	~EditorRandomMap();

protected:		// delete constructer
	EditorRandomMap(const EditorRandomMap& _other) = delete;
	EditorRandomMap(EditorRandomMap&& _other) noexcept = delete;

private:		//delete operator
	EditorRandomMap& operator=(const EditorRandomMap& _other) = delete;
	EditorRandomMap& operator=(const EditorRandomMap&& _other) = delete;

private:
	void Start() override;

public:
	TileIndex GetFloorTileIndex(float4 _Pos);
	TileIndex GetWallTileIndex(float4 _Pos);

public: // 바닥타일정보 생성(그리드 표시)
	void CreateSplitDungeon(int _Width, int _Height);					// 분할된 던전 생성(생성되는 맵의 최대크기를 인자로 얻어온다.) -> 분할완료시 화면에 그리드형태로 렌더링
	void CreateRoomintheDungeon();										// 분할된 던전내에 룸생성(던전기준 타일2개 안쪽으로 룸이 생성) -> 룸 배치완료시 화면에 그리드형태로 렌더링
	void ConnectTheRoom();												// 룸과 룸을 연결 -> 모든 룸연결완료시 화면에 그리드형태로 렌더링

public: // 벽타일정보 생성관련(그리드표시)
	void CreateWall();													// 바닥타일을 체크하여 벽타일을 생성한다.
																		// 단, 문으로 체크하는 구간은 문의 타입(2)를 설정하고,
																		// 벽또한 RT_T, RT_B, RB_L, RB_R, BENT_MULTI, BENT_SINGLE 타입으로 구분하여 설정한다.
																		// -> 모든 벽타일정보를 이용한 벽타입 설정완료시 화면에 그리드형태로 렌더링

public: // 위에서 생성한 바닥/벽타일 정보를 이용하여 렌더러를 매칭
	void RandomMapTileMatching();										// 각 타입별 디폴트 텍스쳐와 매칭하여 렌더링 -> 모든 텍스쳐 매칭완료시 화면에 렌더링

};


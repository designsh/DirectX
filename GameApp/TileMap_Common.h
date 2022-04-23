#pragma once

// 맵타입
enum class MapType
{
	FIXED,		// 고정맵(마을레벨)
	RANDOM,		// 랜덤맵(카타콤레벨, 카오스생츄어리레벨)
};

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

// 오브젝트타일 기본타입
enum class ObjectBasicType
{
	NORMAL,		// 렌더링안함
	WALL,		// 벽으로 판단하므로 오브젝트 배치불가
	OBJECT,		// 오브젝트가 배치되어있음
};

// 바닥타일 정보
struct FloorTileInfo
{
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
	// 인덱스 및 타입정보
	int WallIndexX;
	int WallIndexY;
	int WallTile1ImageIndex;
	int WallTile2ImageIndex;
	WallBasicType WallBasicType;
	WallDetailType WallDetailType;

	// 렌더링 정보
	std::string WallTextureName;
	float4 WallTileSize;
	float4 WallRenderSize;
	float4 WallRenderPivotPos;
};

// 오브젝트타일 정보
struct ObjectTileInfo
{
	// 인덱스 및 타입정보
	int ObjectIndexX;
	int ObjectIndexY;
	int ObjectImageIndex;
	ObjectBasicType ObjectBasicType;

	// 렌더링 정보
	std::string ObjectTextureName;
	float4 ObjectTileSize;
	float4 ObjectRenderSize;
	float4 ObjectRenderPivotPos;
};

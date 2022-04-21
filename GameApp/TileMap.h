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

// �ٴ�Ÿ�� ������Ÿ��
enum class FloorRenderingType
{
	TILE,		// Ÿ�ϸ��
	GRID		// �׸�����
};

// ��Ÿ�� ������Ÿ��
enum class WallRenderingType
{
	TILE1,				// Ÿ�ϸ��(Ÿ��1������ ��ü)
	TILE2,				// Ÿ�ϸ��(Ÿ��2������ ��ü)
	GRID_NOR,			// �׸���(���� �ƴϸ鼭 ���������ϴ� Ÿ��)
	GRID_NONE,			// �׸���(���̸鼭 ���������ϴ� Ÿ��)
	GRID_RT_T,			// �׸�����(RT_T)
	GRID_RT_T_LE,		// �׸�����(RT_T_LE)
	GRID_RT_T_RE,		// �׸�����(RT_T_RE)
	GRID_RT_B,			// �׸�����(RT_B)
	GRID_RT_B_LE,		// �׸�����(RT_B_LE)
	GRID_RT_B_RE,		// �׸�����(RT_B_RE)
	GRID_RB_L,			// �׸�����(RB_L)
	GRID_RB_L_TE,		// �׸�����(RB_L_TE)
	GRID_RB_L_BE,		// �׸�����(RB_L_BE)
	GRID_RB_R,			// �׸�����(RB_R)
	GRID_RB_R_TE,		// �׸�����(RB_R_TE)
	GRID_RB_R_BE,		// �׸�����(RB_R_BE)
	GRID_BENT_SINGLE,	// �׸�����(BENT_SINGLE)
	GRID_BENT_MULTI1,	// �׸�����(BENT_MULTI1)
	GRID_BENT_MULTI2,	// �׸�����(BENT_MULTI2)
};

// ������ƮŸ�� ������Ÿ��(������ ���)
enum class ObjectRenderingType
{
	TILE,
	GRID,
};

// ��Ÿ�� �⺻Ÿ��(���ⱸ��)
enum class WallBasicType
{
	NONE,		// �������Ǵ��ϳ�, ����������
	NORMAL,		// �������Ǵ������ʰ�, ����������

	// RT_T
	RT_T,			// ����(���ϴ�)����(���ӵȺ�) - �߽ɱ���(0,0) ����
	RT_T_RE,		// ���ܹ������� ������ ��(BENT�� ����Ǵ� ��)
	RT_T_LE,		// ���ϴܹ������� ������ ��(BENT������ RT�� ��)

	// RT_B
	RT_B,			// ����(���ϴ�)����(���ӵȺ�) - �߽ɱ���(0,0) �Ʒ���
	RT_B_RE,		// ���ܹ������� �Ʒ����� ��(BENT�� ��)
	RT_B_LE,		// ���ϴܹ������� �Ʒ����� ��(BENT������ RT�� ��)

	// RB_L
	RB_L,			// ���ϴ�(�»��)����(���ӵȺ�) - �߽ɱ���(0,0) ���ʺ�
	RB_L_BE,		// ���ϴܹ������� ���ʺ��� ��(BENT������ RB�� ��)
	RB_L_TE,		// �»�ܹ������� ���ʺ��� ��(BENT�� ��)

	// RB_R
	RB_R,			// ���ϴ�(�»��)����(���ӵȺ�) - �߽ɱ���(0,0) �����ʺ�
	RB_R_BE,		// ���ϴܹ������� �����ʺ��� ��(BENT������ RB�� ��)
	RB_R_TE,		// �»�ܹ������� �����ʺ��� ��(BENT�� ����Ǵ� ��)

	// BENT
	BENT_MULTI,		// ���̴º�(�������� 2�� ������) - �߽ɱ���(0,0) ���ܲ��̴º� => RT_T_RE�� RB_R_TE�� ���������ϴ� ��(��Ƽ������)
	BENT_SINGLE,	// ���̴º�(�������� 1�� ������) - �߽ɱ���(0,0) ���ϴܲ��̴º� => RT_B_LE�� RB_L_BE�� ���������ϴ� ��(�ܵ�������)
};

// ��Ÿ�� ��Ÿ��(���ұ���)
enum class WallDetailType
{
	NORMAL,		// �Ϲݺ�
	DOOR,		// ��
};

// ������ƮŸ�� �⺻Ÿ��
enum class ObjectBasicType
{
	NORMAL,		// ����������
	WALL,		// ������ �Ǵ��ϹǷ� ������Ʈ ��ġ�Ұ�
	OBJECT,		// ������Ʈ�� ��ġ�Ǿ�����
};

// �ٴ�Ÿ�� ����
struct FloorTileInfo
{
	// �ٴ�Ÿ�� ����

	// �ε�������
	int FloorIndexX;
	int FloorIndexY;
	int FloorImageIndex;
	
	// ������ ����
	std::string FloorTextureName;
	float4 FloorTileSize;
	float4 FloorRenderSize;
	float4 FloorRenderPivotPos;
};

// ��Ÿ�� ����
struct WallTileInfo
{
	// �ε��� �� Ÿ������
	int WallIndexX;
	int WallIndexY;
	int WallTile1ImageIndex;
	int WallTile2ImageIndex;
	WallBasicType WallBasicType;
	WallDetailType WallDetailType;

	// ������ ����
	std::string WallTextureName;
	float4 WallTileSize;
	float4 WallRenderSize;
	float4 WallRenderPivotPos;
};

// ������ƮŸ�� ����
struct ObjectTileInfo
{
	// �ε��� �� Ÿ������
	int ObjectIndexX;
	int ObjectIndexY;
	int ObjectImageIndex;
	ObjectBasicType ObjectBasicType;

	// ������ ����
	std::string ObjectTextureName;
	float4 ObjectTileSize;
	float4 ObjectRenderSize;
	float4 ObjectRenderPivotPos;
};

class GameEngineTileMapRenderer;
struct WallTileRender
{
	GameEngineTileMapRenderer* Tiles1_;
	GameEngineTileMapRenderer* Tiles2_;
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTileMapRenderer;
class TileMap : public GameEngineActor
{
#pragma region �������� Ÿ������
private: // ���������� ����Ǵ� Ÿ������(����)
	std::vector<std::vector<FloorTileInfo>> FloorTileInfo_;
	std::vector<std::vector<WallTileInfo>> WallTileInfo_;
	std::vector<std::vector<ObjectTileInfo>> ObjectTileInfo_;
#pragma endregion

#pragma region �����Ϳ뵵
private: // �ؽ��� ��Ī
	std::string FloorTileTextureName_;
	std::string WallTileTextureName_;
	std::string ObjectTileTextureName_;

private: // ������ ȭ�� ������ �뵵
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;
	std::unordered_map<__int64, WallTileRender> WallTiles_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> ObjectTiles_;

	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorGrides_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallGrides_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> ObjectGrides_;

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

private: // ������ƮŸ������
	float4 ObjectTileImageSizeHalf_;
	float4 ObjectTileImageSize_;
	float4 ObjectTileIndexPivotPos_;

private: // ���������
	FloorRenderingType FloorRenderingType_;
	WallRenderingType WallRenderingType_;
	ObjectRenderingType ObjectRenderingType_;

#pragma endregion

#pragma region ��Ÿ�� Ư������ �̹����ε���
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

#pragma region �׸���On/Off���°�
	bool FloorGridesActive_;
	bool WallGridesActive_;
	bool ObjectGridesActive_;
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

public: // ��������� ����
	void SetFloorRenderingMode(FloorRenderingType _FloorRenderingType);
	void SetWallRenderingMode(WallRenderingType _WallRenderingType);
	void SetObjectRenderingMode(ObjectRenderingType _ObjectRenderingType);

public: // ���� ��������� Get
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

public: // IMGUI Window ǥ�ÿ�
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
	// Ÿ������ ���� : �� ���ǿ� �°� ó���Ǹ� ���������� �Ϸ�Ǹ�, �׸������·� ȭ�鿡 �������Ѵ�.
	void CreateFloorTileInfo(int _WidthTileCount, int _HeightTileCount, int _ImageIndex);	// ���ڷ� ������ �ʺ�/���� �ε����� �̿��Ͽ� �ٴ�Ÿ�� ���� �� �׸��� ����
	void CreateWallTileInfo();																// ��Ÿ���� ������ �ٴ�Ÿ�� ������ ����Ͽ� ����
	void CreateObjectTileInfo();															// ��Ÿ�ϻ����� �Ϸ�� �� ȣ��Ǿ� ������Ʈ ��ġ�� ���� ������������

	// ������ �ٴ�Ÿ�� ������ �̿��Ͽ� Ư�� ���ǿ� �ش��ϴ� Ÿ���� ������ ��� Ÿ���� ����ƮŸ�Ϸ� ��������
	void UpdateFloorTileInfo();

	// ������ �ٴ�Ÿ�� ������ �̿��Ͽ� Ư�� ���ǿ� �ش��ϴ� Ÿ���� ������ ��� Ÿ���� ����ƮŸ�Ϸ� ��������
	// 1. �� ACT�� ���Ǻ� �̹������� ��Ī
	void SetTownWallTexture();
	void SetCatacombsWallTexture();
	void SetChaosSanctuaryWallTexture();

	// 2. 1.���� ������ Ÿ�Ϸ� ���� �ؽ��� ��Ī �� ���� ����
	void UpdateWallTileInfo();
	
	// ���� �ڵ������� ��� Ÿ������ �� ������ ���� ����
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
};


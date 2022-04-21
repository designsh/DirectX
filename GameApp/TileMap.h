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

// ������Ÿ��
enum class TileRenderingType
{
	ALL,		// �׸���+Ÿ��
	GRID,		// �׸���
	TILE		// Ÿ��
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
	// ��Ÿ�� ����

	// �ε��� �� Ÿ������
	int WallIndexX;
	int WallIndexY;
	int WallImageIndex;
	WallBasicType WallBasicType;
	WallDetailType WallDetailType;

	// ������ ����
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
#pragma endregion

#pragma region �����Ϳ뵵
private: // �ؽ��� ��Ī
	std::string FloorTileTextureName_;
	std::string WallTileTextureName_;

private: // ������ ȭ�� ������ �뵵
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;


	std::unordered_map<__int64, WallTileRender> WallTiles_;

	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorGrides_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallGrides_;

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

private: // ���������
	TileRenderingType TileRenderingType_;

#pragma endregion

#pragma region Ư�����Ǻ�Ÿ���̹����ε���
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

public: // ��������� ����
	void SetTileRenderingMode(TileRenderingType _RenderingType);

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
	void DelFloorTile(float4 _Pos);
	void DelWallTile(float4 _Pos);

public: // CreateAutoMap Mode
	// Ÿ������ ���� : �� ���ǿ� �°� ó���Ǹ� ���������� �Ϸ�Ǹ�, �׸������·� ȭ�鿡 �������Ѵ�.
	void CreateFloorTileInfo(int _WidthTileCount, int _HeightTileCount, int _ImageIndex);
	void CreateWallTileInfo(); // ��Ÿ���� ������ �ٴ�Ÿ�� ������ ����Ͽ� �����ȴ�.

	// ������ �ٴ�Ÿ�� ������ �̿��Ͽ� Ư�� ���ǿ� �ش��ϴ� Ÿ���� ������ ��� Ÿ���� ����ƮŸ�Ϸ� ��������
	void UpdateFloorTileInfo();

	// ������ �ٴ�Ÿ�� ������ �̿��Ͽ� Ư�� ���ǿ� �ش��ϴ� Ÿ���� ������ ��� Ÿ���� ����ƮŸ�Ϸ� ��������
	// 1. �� ACT�� ���Ǻ� �̹������� ��Ī
	void SetTownWallTexture();
	void SetCatacombsWallTexture();
	void SetChaosSanctuaryWallTexture();

	// 2. 1.���� ������ Ÿ�Ϸ� ���� �ؽ��� ��Ī �� ���� ����
	void UpdateWallTileInfo();
	
	

	

	// ���� ������ ��� Ÿ������ �� ������ ���� ����
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


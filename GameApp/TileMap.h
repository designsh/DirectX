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
	NONE,		// �������� �����ϳ�, ��������������
	RT,			// ����(���ϴ�)����
	RB,			// ���ϴ�(�»��)����
	BENT,		// ���̴º�
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
	std::unordered_map<__int64, GameEngineTileMapRenderer*> WallTiles_;

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
	void CreateFloorTileInfo(int _WidthTileCount, int _HeightTileCount);
	void CreateWallTileInfo(); // ��Ÿ���� ������ �ٴ�Ÿ�� ������ ����Ͽ� �����ȴ�.

	// ������ ������ �̿��Ͽ� Ư�� ���ǿ� �ش��ϴ� Ÿ���� ������ ��� Ÿ���� ����ƮŸ�Ϸ� ��������
	void UpdateFloorTileInfo(int _DefaultTileIndex);
	void UpdateWallTileInfo(int _DefaultTileIndex);

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


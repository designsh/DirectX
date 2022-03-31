#pragma once
#include <GameEngine/GameEngineActor.h>

union TileIndex
{
	struct 
	{
		int X_;
		int Y_;
	};

	__int64 Index_;
};

// �з� : �ִϸ��̼�
// �뵵 : Ÿ��Ʋ���� �ΰ�
// ���� : 
class GameEngineUIRenderer;
class IsoTileMap : public GameEngineActor
{
public:
	// constrcuter destructer
	IsoTileMap();
	~IsoTileMap();

	// delete Function
	IsoTileMap(const IsoTileMap& _Other) = delete;
	IsoTileMap(IsoTileMap&& _Other) noexcept = delete;
	IsoTileMap& operator=(const IsoTileMap& _Other) = delete;
	IsoTileMap& operator=(IsoTileMap&& _Other) noexcept = delete;

	void SetTile(float4 _Pos, float4 _CamPos);

	TileIndex GetIndex(float4 _Pos, float4 _CamPos);

	float4 GetIsoPos(float4 _Pos);


private:
	void Start() override;

	float4 TileSize;
	float4 TileSizeHalf;
	float4 IndexPivotPos;
	// 8 ����Ʈ
	std::unordered_map<__int64, class GameEngineImageRenderer*> Tiles_;


private:

};


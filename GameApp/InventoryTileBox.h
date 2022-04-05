#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

#include "MainPlayerInfomation.h"

// 분류 : 타일
// 용도 : 인벤토리 아이템 배치
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InventoryTileBox : public GameEngineActor
{
private:	// member Var
	bool ArrangementFlag_;									// 배치 Flag(해당 박스에 아이템이 존재하면(배치되어있다면) true)
	ItemLocType BoxTileType_;								// 타일박스 타입(NORMAL : 플레이어의 장착상태와 무관)
	int Index_;												// 총 인덱스
	int IndexX_;											// x 인덱스
	int IndexY_;											// y 인덱스
	float4 Pos_;											// 위치
	float4 Scale_;											// 크기

private:
	GameEngineUIRenderer* TileBoxRenderer_;					// 타일박스 렌더러
	GameEngineCollision* TileBoxCollider_;					// 타일박스 충돌체
	Button_State TileBoxButtonState_;						// 타일박스 충돌체 클릭 상태

private:
	GameEngineUIRenderer* TileBoxItemEquipRenderer_;		// 아이템용 렌더러(아이템배치시 아이템텍스쳐 셋팅)
	std::string CurBatchItemName_;							// 현재 타일에 배치되어있는 아이템명
	float4 BatchItemScale_;									// 배치된 아이템의 실제 렌더러 크기

public:
	InventoryTileBox();
	~InventoryTileBox();

protected:		// delete constructer
	InventoryTileBox(const InventoryTileBox& _other) = delete;
	InventoryTileBox(InventoryTileBox&& _other) noexcept = delete;

private:		//delete operator
	InventoryTileBox& operator=(const InventoryTileBox& _other) = delete;
	InventoryTileBox& operator=(const InventoryTileBox&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void BoxTileClick(GameEngineCollision* _Other);

public:
	void ItemEquipCheck();

public:
	void GameStartItemBatch(const std::string& _ItemName, int _ItemCode, int _WidthSize, int _HeightSize);

public:
	void TileBoxActive();
	void TileBoxInactive();

public:
	void CreateNormalTileBox(bool _ArrangementFlag, ItemLocType _BoxTileType, int _X, int _Y, int _Index);
	void CreatePlayerEquipTileBox(const std::string& _TextureName, bool _ArrangementFlag, ItemLocType _BoxTileType, int _Index, float4 _Pos, float4 _Scale);
};


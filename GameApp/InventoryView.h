#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

enum class InvTabType
{
	NONE = -1,
	EQUIP,		// 상단 장착탭
	NORMAL,		// 하단 보관탭
	MAX
};

class GameEngineUIRenderer;
struct ItemInfo
{
	float4 Pos_;
	float4 RenderScale_;

	GameEngineUIRenderer* ItemRenderer_;


	int Index_;
	int StartIndex_;
	int WidthIndex_;
	int HeightIndex_;
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InventoryTileBox;
class InventoryView : public GameEngineActor
{
#pragma region 인벤창 기본정보
private:	// member Var
	GameEngineUIRenderer* InventoryPanel_;

private:
	GameEngineUIRenderer* CloseButton_;
	GameEngineCollision* CloseButtonCollider_;
	Button_State CloseButtonState_;

private:
	InvTabType InvTabType_;
#pragma endregion

#pragma region 인벤창 상단/하단 타일박스정보
private:
	std::vector<InventoryTileBox*> InvEquipInfo_;		// 장착탭(무기, 방어구, ...) 정보목록
	std::vector<GameEngineCollision*> InvEquipCol_;		// 장착탭(무기, 방어구, ...) 충돌체목록
	
	std::vector<InventoryTileBox*> InvStoreInfo_;		// 보관탭 정보목록
	std::vector<GameEngineCollision*> InvStoreCol_;		// 보관탭 충돌체 목록

private:
	std::vector<ItemInfo> InvBatchItemList_;			// 인벤창에 배치되어있는 아이템정보 목록
#pragma endregion

#pragma region 인벤창 상단/하단 배치된 아이템
private:


#pragma endregion

public:
	InventoryView();
	~InventoryView();

protected:		// delete constructer
	InventoryView(const InventoryView& _other) = delete;
	InventoryView(InventoryView&& _other) noexcept = delete;

private:		//delete operator
	InventoryView& operator=(const InventoryView& _other) = delete;
	InventoryView& operator=(const InventoryView&& _other) = delete;

private:
	void CloseButtonClick(GameEngineCollision* _Other);
	void EquipTileBoxClick(GameEngineCollision* _Other, int _Index);	// 충돌한 타일의 인덱스를 받아온다.
	void StoreTileBoxClick(GameEngineCollision* _Other, int _Index);	// 충돌한 타일의 인덱스를 받아온다.

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetInventoryBoxTileActvie();
	void SetInentroyBoxTileInactive();

public: // 인벤창 초기셋팅
	void InitInventoryView();
	void CreateInvTile();
	void CreateInvTileInfo();
	void CreateInvTileCol();
	void PlayerItemListBatch();
	
public: // 인벤창 아이템 배치/해제/이동
	void ItemBatchOn(int _TileIndex, InvTabType _InvTabType);
	void ItemBatchOff(int _TileIndex, InvTabType _InvTabType);


public: // 
	
};


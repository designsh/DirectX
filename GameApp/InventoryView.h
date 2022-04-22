#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "MainPlayerInfomation.h"
#include "AllNPCInfomation.h"

enum class InvTabType
{
	NONE = -1,
	EQUIP,		// 상단 장착탭
	NORMAL,		// 하단 보관탭
	MAX
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InventoryTileBox;
class InvArrangementItemInfo;
class GameEngineLevel;
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

#pragma region 인벤창 상단/하단 타일박스정보 & 배치된 아이템목록
private:
	std::vector<InventoryTileBox*> InvEquipInfo_;				// 장착탭(무기, 방어구, ...) 정보목록
	std::vector<GameEngineCollision*> InvEquipCol_;				// 장착탭(무기, 방어구, ...) 충돌체목록
	
	std::vector<InventoryTileBox*> InvStoreInfo_;				// 보관탭 정보목록
	std::vector<GameEngineCollision*> InvStoreCol_;				// 보관탭 충돌체 목록

private:
	std::vector<InvArrangementItemInfo*> InvArrItemList_;		// 인벤창에 배치되어있는 아이템정보 목록
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
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
	bool GetInvenCurEquipState(ItemLocType _LocType = ItemLocType::Inven_Weapon);

public:
	void SetInventoryBoxTileActvie();
	void SetInentroyBoxTileInactive();

public: // 인벤창 초기셋팅
	void InitInventoryView();
	void CreateInvTile();
	void CreateInvTileInfo();
	void CreateInvTileCol();
	void PlayerItemListArrangement();
	
public: // 인벤창 마우스와 연동하여 아이템 배치/해제
	void ItemArrangementOn(int _TileIndex, InvTabType _InvTabType);
	void ItemArrangementOff(int _TileIndex, InvTabType _InvTabType);

public: // 인벤창과 판매창, 마우스가 연동하여 특수기능 수행
	void ItemSellProcess(int _TileIndex, InvTabType _InvTabType, NPCType _BuySellType);
	void ItemRepairProcess(int _TileIndex, InvTabType _InvTabType);

public: // 외부에서 접근하여 현재 인벤토리에 아이템이 배치가능한지 체크하는 기능 수행(아이템이 차지하는 타일의 인덱스(가로/세로)를 수신)
	bool InventoryArrangeTileCheckOn(const float4& _ItemScaleIndex, const std::string& _ItemName);

public: // 인벤창 상단 장착탭의 무기 장착상태에 따라 플레이어 상태 변경
	void EquipItemCheck(ItemLocType _ItemLocType, const std::string& _ItemName, bool _OnAndOff);
};


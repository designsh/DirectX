#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "MainPlayerInfomation.h"

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
class InventoryView : public GameEngineActor
{
#pragma region 인벤창 아이템정보
	class ItemInfo
	{
	private:
		int Index_;								// 아이템정보목록에서의 인덱스
		ItemLocType CurItemLoc_;				// 해당 아이템의 배치 위치
		std::vector<int> ItemArrIndexs_;		// 배치위치가 NORMAL이라면 아이템이 차지하는 타일인덱스목록
		
	private:
		std::string ItemTextureName_;			// 아이템 텍스쳐명 
		std::string ItemName_;					// 아이템명
		int ItemCode_;							// 아이템코드
		float4 ItemScale_;						// 아이템렌더러 크기

	private:
		GameEngineUIRenderer* ItemRenderer_;	// 아이템 렌더러
		GameEngineCollision* ItemCollision_;	// 아이템 충돌체

	public:
		// 아이템 정보 생성
		bool CreateItemInfo(int _Index, ItemLocType _LocType, const std::string& _ItemName_);

	public:	
		// 하단 보관탭에 배치되는 아이템이며, 아이템이 차지하는 타일의 인덱스가 1이 아닌 아이템은 
		// 본인이 차지하는 타일의 인덱스를 모두 알고있는다.
		void SetItemArrIndexs(std::vector<int> _TileIndex);
	};

#pragma endregion

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
	std::vector<ItemInfo*> InvArrItemList_;				// 인벤창에 배치되어있는 아이템정보 목록
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
	void PlayerItemListArrangement();
	
public: // 인벤창 아이템 배치/해제/이동
	void ItemArrangementOn(int _TileIndex, InvTabType _InvTabType);
	void ItemArrangementOff(int _TileIndex, InvTabType _InvTabType);


public: // 
	
};


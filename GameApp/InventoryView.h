#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "MainPlayerInfomation.h"

union InvBoxIndex
{
	struct
	{
		int X_;
		int Y_;
	};

	__int64 Index_;
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InventoryTileBox;
class InventoryView : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* InventoryPanel_;

private:
	GameEngineUIRenderer* CloseButton_;
	GameEngineCollision* CloseButtonCollider_;
	Button_State CloseButtonState_;

private: // 인벤토리 정보
	// 수정중
	std::vector<GameEngineCollision*> InventoryColTiles_;					// 인벤토리창 충돌체 배치목록
	std::map<InvBoxIndex, GameEngineUIRenderer*> InventoryItemRenderers_;	// 인벤토리창에 배치중인 아이템목록



	// 수정전
	std::vector<InventoryTileBox*> NormalInventoryTile_;		// 인벤토리창 하단 박스(보유아이템목록타일박스목록)
	std::vector<InventoryTileBox*> PlayerEquipInvTile_;			// 인벤토리창 상단 박스(플레이어 장착용 타일박스목록)

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
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void CloseButtonClick(GameEngineCollision* _Other);

public:
	void InitInventoryView();
	void CreateInventoryTile();
	void InitInventoryItemSetting(const std::string& _ItemName, int _ItemCode, ItemLocType _ItemLocType, int _StartIndex, int _WidthSize, int _HeightSize);

public:
	void SetInventoryBoxTileActvie();
	void SetInentroyBoxTileInactive();

};


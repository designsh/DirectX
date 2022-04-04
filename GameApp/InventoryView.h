#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "MainPlayerInfomation.h"

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


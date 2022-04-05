#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

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
#pragma endregion

#pragma region 인벤창 상단 장착탭정보
private:
	std::vector<InventoryTileBox*> InvEquipInfo_;



#pragma endregion

#pragma region 인벤창 하단 보관탭정보
private:
	std::vector<GameEngineCollision*> InvStoreInfo_;



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

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public: // 인벤창 초기셋팅
	void InitInventoryView();

public: // 


public: // 
	
};


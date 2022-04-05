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

};


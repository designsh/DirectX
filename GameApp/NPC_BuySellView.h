#pragma once
#include <GameEngine/GameEngineActor.h>
#include "AllNPCInfomation.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class NPC_BuySellView : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* ViewPanel_;					// 판매창 판넬렌더러

private: // 버튼관련
	GameEngineUIRenderer* BuyButtonRenderer_;			// 구매 버튼 렌더러
	GameEngineCollision* BuyButtonCollider_;			// 구매 버튼 충돌체
	GameEngineUIRenderer* SellButtonRenderer_;			// 판매 버튼 렌더러
	GameEngineCollision* SellButtonCollider_;			// 판매 버튼 충돌체
	GameEngineUIRenderer* RepairButtonRenderer_;		// 수리 버튼 렌더러
	GameEngineCollision* RepairButtonCollider_;			// 수리 버튼 충돌체
	GameEngineUIRenderer* AllRepairButtonRenderer_;		// 전부수리 버튼 렌더러
	GameEngineCollision* AllRepairButtonCollider_;		// 전부수리 버튼 충돌체
	
private:
	NPCClassType NPCClassType_;							// NPC 클래스 타입
	NPCType BuySellViewType_;							// 판매창타입

public:
	NPC_BuySellView();
	~NPC_BuySellView();

protected:		// delete constructer
	NPC_BuySellView(const NPC_BuySellView& _other) = delete;
	NPC_BuySellView(NPC_BuySellView&& _other) noexcept = delete;

private:		//delete operator
	NPC_BuySellView& operator=(const NPC_BuySellView& _other) = delete;
	NPC_BuySellView& operator=(const NPC_BuySellView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void BuyButtonClick(GameEngineCollision* _Other);
	void SellButtonClick(GameEngineCollision* _Other);
	void RepairButtonClick(GameEngineCollision* _Other);
	void AllRepairButtonClick(GameEngineCollision* _Other);

public:
	void CreateBuySellView(NPCType _BuySellViewType, NPCClassType _NPCClassType);

public:
	void NPCBuySellViewActive();
	void NPCBuySellViewInactive();
};


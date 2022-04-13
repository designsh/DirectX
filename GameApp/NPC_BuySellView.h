#pragma once
#include <GameEngine/GameEngineActor.h>
#include "AllNPCInfomation.h"
#include "GlobalEnumClass.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class NPC_BuySellView : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* ViewPanel_;					// �Ǹ�â �ǳڷ�����

private: // ��ư����
	GameEngineUIRenderer* BuyButtonRenderer_;			// ���� ��ư ������
	GameEngineCollision* BuyButtonCollider_;			// ���� ��ư �浹ü
	GameEngineUIRenderer* SellButtonRenderer_;			// �Ǹ� ��ư ������
	GameEngineCollision* SellButtonCollider_;			// �Ǹ� ��ư �浹ü
	GameEngineUIRenderer* RepairButtonRenderer_;		// ���� ��ư ������
	GameEngineCollision* RepairButtonCollider_;			// ���� ��ư �浹ü
	GameEngineUIRenderer* AllRepairButtonRenderer_;		// ���μ��� ��ư ������
	GameEngineCollision* AllRepairButtonCollider_;		// ���μ��� ��ư �浹ü
	
private:
	NPCClassType NPCClassType_;							// NPC Ŭ���� Ÿ��
	NPCType BuySellViewType_;							// �Ǹ�âŸ��

private:
	bool BuyActive_;									// ���� Ȱ��ȭ Flag
	bool SellActive_;									// �Ǹ� Ȱ��ȭ Flag
	bool RepairActive_;									// ���� Ȱ��ȭ Flag
	Button_State BuyBtnState_;							// ���Ź�ư ����
	Button_State SellBtnState_;							// �ǸŹ�ư ����
	Button_State RepairBtnState_;						// ������ư ����
	
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


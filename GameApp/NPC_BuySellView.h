#pragma once
#include <GameEngine/GameEngineActor.h>
#include "AllNPCInfomation.h"
#include "GlobalEnumClass.h"

// �Ǹ�â�� �����۹�ġŸ������
class GameEngineUIRenderer;
struct ArrangeTileInfo
{
	bool ItemArrangementFlag_;								// �ش� Ÿ���� ��ġ�Ϸ� Flag(�������� ��ġ�Ǿ��ٸ� true)
	int Index_;												// �ش� Ÿ���� �Ѱ��ε���
	int IndexX_;											// �ش� Ÿ���� X �ε���
	int IndexY_;											// �ش� Ÿ���� Y �ε���
	float4 TileScale_;										// �ش� Ÿ���� ũ��
	float4 TilePos_;										// �ش� Ÿ���� ��ġ
	GameEngineUIRenderer* TileRenderer_;					// �ش� Ÿ���� ������(������ ��ġ�� Blue Color)
};

// �������ִ� �������� ����
class GameEngineUIRenderer;
struct HaveItem
{
	bool OneSize_;											// �ش� �������� ũ�Ⱑ 1x1�϶� true
	int StartIndex;											// �ش� �������� ũ�Ⱑ 1x1�϶� �����ϴ� �ε���
	std::vector<int> ArrangeIndexs_;						// �ش� �������� ũ�Ⱑ 1x1�� �ƴҶ� �����ϴ� �ε������
	ItemList ItemInfo_;										// �ش� �������� �⺻����(�̸�, �Ǹűݾ�, ...)
	GameEngineUIRenderer* ItemRenderer_;					// �ش� ������ ������
	float4 RenderPos_;										// �ش� �����۷����� ��ġ
};

// �Ǹ�â�� ������
class GameEngineUIRenderer;
class GameEngineCollision;
struct TabInfo
{
	int TabIndex_;											// �� �ε���
	bool TabActive_;										// �� Ȱ��ȭ����(���ý� true)
	GameEngineUIRenderer* TabRenderer_;						// �� ������
	GameEngineCollision* TabCollision_;						// �� �浹ü
	ItemLocType TabType_;									// �ش� ���� Ÿ��(�Ǹ�â - ������, �Ǹ�â - ����, �Ǹ�â - ��Ÿ��)
	std::vector<ArrangeTileInfo> ArrangeTiles_;				// �ش� ���� ��ġŸ������
	std::vector<HaveItem> HaveItemList_;					// �ش� ���� �����ϰ��ִ� �����۸��
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class NPC_BuySellView : public GameEngineActor
{
private:
	static int CurTabIndex;									// �ش� �Ǹ�â�� ���� ���ε���

public:
	static int GetCurTabIndex();

private: // �ǳڰ���
	GameEngineUIRenderer* ViewPanel_;						// �Ǹ�â �ǳڷ�����

private: // ��ư����
	GameEngineUIRenderer* BuyButtonRenderer_;				// ���� ��ư ������
	GameEngineCollision* BuyButtonCollider_;				// ���� ��ư �浹ü
	GameEngineUIRenderer* SellButtonRenderer_;				// �Ǹ� ��ư ������
	GameEngineCollision* SellButtonCollider_;				// �Ǹ� ��ư �浹ü
	GameEngineUIRenderer* AllRepairButtonRenderer_;			// ���μ��� ��ư ������
	GameEngineCollision* AllRepairButtonCollider_;			// ���μ��� ��ư �浹ü
	GameEngineUIRenderer* CloseButtonRenderer_;				// â�ݱ� ��ư ������
	GameEngineCollision* CloseButtonCollider_;				// â�ݱ� ��ư �浹ü

private: // ����������
	std::vector<TabInfo> BuySellViewTabs_;					// �� �Ǹ�â�� ������(�����۸��, ��ġ����, �ε���, ...)

private: // Ÿ��
	std::vector<GameEngineCollision*> ArrangeTileCols_;		// �� �Ǹ�â�� ��ġŸ�� �浹ü

private: // NPC Ÿ�� �� �Ǹ�â Ÿ��
	NPCClassType NPCClassType_;								// NPC Ŭ���� Ÿ��
	NPCType BuySellViewType_;								// �Ǹ�âŸ��

private:
	int HaveGold_;											// �ش� �Ǹ�â(NPC)�� �����ϰ��ִ� ���
															// 1. �÷��̾ �����۱��Ž� �ش� ��差����
															// 2. �÷��̾ �������ǸŽ� �ش� ��差����

private: // Ư����� ��ư����
	bool BuyActive_;										// ���� Ȱ��ȭ Flag
	bool SellActive_;										// �Ǹ� Ȱ��ȭ Flag
	bool AllRepairActive_;									// ���μ��� Ȱ��ȭ Flag
	Button_State BuyBtnState_;								// ���Ź�ư ����
	Button_State SellBtnState_;								// �ǸŹ�ư ����
	Button_State AllRepairBtnState_;						// ���μ�����ư ����
	Button_State CloseBtnState_;							// â�ݱ��ư ����
	
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

private: // �� ��ư Ŭ��üũ
	void BuyButtonClick(GameEngineCollision* _Other);
	void SellButtonClick(GameEngineCollision* _Other);
	void AllRepairButtonClick(GameEngineCollision* _Other);
	void CloseButtonClick(GameEngineCollision* _Other);

public: // Ÿ�Ժ� �Ǹ�â ����
	void CreateBuySellView(NPCType _BuySellViewType, NPCClassType _NPCClassType);

public: // �Ǹ�â Ȱ��ȭ/��Ȱ��ȭ ó��
	void NPCBuySellViewActive();
	void NPCBuySellViewInactive();

public: // �Ǹ�â �ǰ� �浹ó��
	void SelectTabClick(GameEngineCollision* _Other, int _Index);

public: // �Ǹ�â ��ġŸ�ϰ� �浹ó��
	void ArrangeTileClick(GameEngineCollision* _Other, int _Index);
};


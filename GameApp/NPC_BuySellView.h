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
	int ItemRemainsQuantity_;								// �ش� ������ ���� ����(�⺻ ��ȭ:999, ����:1)
	float4 RenderPos_;										// �ش� �����۷����� ��ġ
	GameEngineUIRenderer* ItemRenderer_;					// �ش� ������ ������
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
private: // �ǳڰ���
	GameEngineUIRenderer* ViewPanel_;						// �Ǹ�â �ǳڷ�����

private: // ��ư����
	GameEngineUIRenderer* BuyButtonRenderer_;				// ���� ��ư ������
	GameEngineCollision* BuyButtonCollider_;				// ���� ��ư �浹ü
	GameEngineUIRenderer* SellButtonRenderer_;				// �Ǹ� ��ư ������
	GameEngineCollision* SellButtonCollider_;				// �Ǹ� ��ư �浹ü
	GameEngineUIRenderer* RepairButtonRenderer_;			// ���� ��ư ������
	GameEngineCollision* RepairButtonCollider_;				// ���� ��ư �浹ü
	GameEngineUIRenderer* AllRepairButtonRenderer_;			// ���μ���/â�ݱ� ��ư ������(������� : ���μ�����ư, ��ȭ���� : â�ݱ��ư)
	GameEngineCollision* AllRepairButtonCollider_;			// ���μ���/â�ݱ� ��ư �浹ü(������� : ���μ�����ư, ��ȭ���� : â�ݱ��ư)

private: // ����������
	std::vector<TabInfo> BuySellViewTabs_;					// �� �Ǹ�â�� ������(�����۸��, ��ġ����, �ε���, ...)

private: // Ÿ��
	std::vector<GameEngineCollision*> ArrangeTileCols_;		// �� �Ǹ�â�� ��ġŸ�� �浹ü

private: // NPC Ÿ�� �� �Ǹ�â Ÿ��
	NPCClassType NPCClassType_;								// NPC Ŭ���� Ÿ��
	NPCType BuySellViewType_;								// �Ǹ�âŸ��

private:
	GameEngineUIRenderer* HaveGoldRenderer_;				// ��差 ������
	int HaveGold_;											// �ش� �Ǹ�â(NPC)�� �����ϰ��ִ� ���
															// 1. �÷��̾ �����۱��Ž� �ش� ��差����
															// 2. �÷��̾ �������ǸŽ� �ش� ��差����

private: // Ư����� ��ư����
	bool BuyActive_;										// ���� Ȱ��ȭ Flag
	bool SellActive_;										// �Ǹ� Ȱ��ȭ Flag
	bool RepairActive_;										// ���� Ȱ��ȭ Flag
	Button_State BuyBtnState_;								// ���Ź�ư ����
	Button_State SellBtnState_;								// �ǸŹ�ư ����
	Button_State RepairBtnState_;							// ������ư ����
	Button_State AllRepairBtnState_;						// ���μ���/â�ݱ� ��ư ����

private:
	int CurTabIndex;										// �ش� �Ǹ�â�� ���� ���ε���
	
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
	void RepairButtonClick(GameEngineCollision* _Other);
	void AllRepairButtonClick(GameEngineCollision* _Other);

private: // ���ο��� ���� �Ǹ�â ��Ȱ��ȭó��
	void PrivateNPCBuySellViewActive();

public: // �ܺο��� ���� �Ǹ�â Ȱ��ȭ/��Ȱ��ȭ ó��
	void PublicNPCBuySellViewActive();
	void PublicNPCBuySellViewInactive();

public: // Ÿ�Ժ� �Ǹ�â ����
	void CreateBuySellView(NPCType _BuySellViewType, NPCClassType _NPCClassType);

public: // �Ǹ�â �ǰ� �浹ó��
	void SelectTabClick(GameEngineCollision* _Other, int _Index);

public: // �Ǹ�â ��ġŸ�ϰ� �浹ó��
	void ArrangeTileClick(GameEngineCollision* _Other, int _Index);

public: // ����Ÿ�Ժ� �����۸�ϻ���
	void CreateItemList(int _TabIndex);
	std::string FindChandleryItem(int _ArrangeIndex);
	std::string FindWeaponItem(int _ArrangeIndex);
	int FindItemListIndex(const std::string& _ItemName);
	float4 GetItemScale(const std::string& _ItemName);

public: // ������� ����/����
	void AddHaveGold(int _Gold);
	void SubHaveGold(int _Gold);
};


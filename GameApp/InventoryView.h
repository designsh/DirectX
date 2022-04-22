#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "MainPlayerInfomation.h"
#include "AllNPCInfomation.h"

enum class InvTabType
{
	NONE = -1,
	EQUIP,		// ��� ������
	NORMAL,		// �ϴ� ������
	MAX
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InventoryTileBox;
class InvArrangementItemInfo;
class GameEngineLevel;
class InventoryView : public GameEngineActor
{
#pragma region �κ�â �⺻����
private:	// member Var
	GameEngineUIRenderer* InventoryPanel_;

private:
	GameEngineUIRenderer* CloseButton_;
	GameEngineCollision* CloseButtonCollider_;
	Button_State CloseButtonState_;

private:
	InvTabType InvTabType_;
#pragma endregion

#pragma region �κ�â ���/�ϴ� Ÿ�Ϲڽ����� & ��ġ�� �����۸��
private:
	std::vector<InventoryTileBox*> InvEquipInfo_;				// ������(����, ��, ...) �������
	std::vector<GameEngineCollision*> InvEquipCol_;				// ������(����, ��, ...) �浹ü���
	
	std::vector<InventoryTileBox*> InvStoreInfo_;				// ������ �������
	std::vector<GameEngineCollision*> InvStoreCol_;				// ������ �浹ü ���

private:
	std::vector<InvArrangementItemInfo*> InvArrItemList_;		// �κ�â�� ��ġ�Ǿ��ִ� ���������� ���
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
	void EquipTileBoxClick(GameEngineCollision* _Other, int _Index);	// �浹�� Ÿ���� �ε����� �޾ƿ´�.
	void StoreTileBoxClick(GameEngineCollision* _Other, int _Index);	// �浹�� Ÿ���� �ε����� �޾ƿ´�.

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
	bool GetInvenCurEquipState(ItemLocType _LocType = ItemLocType::Inven_Weapon);

public:
	void SetInventoryBoxTileActvie();
	void SetInentroyBoxTileInactive();

public: // �κ�â �ʱ����
	void InitInventoryView();
	void CreateInvTile();
	void CreateInvTileInfo();
	void CreateInvTileCol();
	void PlayerItemListArrangement();
	
public: // �κ�â ���콺�� �����Ͽ� ������ ��ġ/����
	void ItemArrangementOn(int _TileIndex, InvTabType _InvTabType);
	void ItemArrangementOff(int _TileIndex, InvTabType _InvTabType);

public: // �κ�â�� �Ǹ�â, ���콺�� �����Ͽ� Ư����� ����
	void ItemSellProcess(int _TileIndex, InvTabType _InvTabType, NPCType _BuySellType);
	void ItemRepairProcess(int _TileIndex, InvTabType _InvTabType);

public: // �ܺο��� �����Ͽ� ���� �κ��丮�� �������� ��ġ�������� üũ�ϴ� ��� ����(�������� �����ϴ� Ÿ���� �ε���(����/����)�� ����)
	bool InventoryArrangeTileCheckOn(const float4& _ItemScaleIndex, const std::string& _ItemName);

public: // �κ�â ��� �������� ���� �������¿� ���� �÷��̾� ���� ����
	void EquipItemCheck(ItemLocType _ItemLocType, const std::string& _ItemName, bool _OnAndOff);
};


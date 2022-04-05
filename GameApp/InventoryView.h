#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

enum class InvTabType
{
	NONE = -1,
	EQUIP,		// ��� ������
	NORMAL,		// �ϴ� ������
	MAX
};

class GameEngineUIRenderer;
struct ItemInfo
{
	float4 Pos_;
	float4 RenderScale_;

	GameEngineUIRenderer* ItemRenderer_;


	int Index_;
	int StartIndex_;
	int WidthIndex_;
	int HeightIndex_;
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class InventoryTileBox;
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

#pragma region �κ�â ���/�ϴ� Ÿ�Ϲڽ�����
private:
	std::vector<InventoryTileBox*> InvEquipInfo_;		// ������(����, ��, ...) �������
	std::vector<GameEngineCollision*> InvEquipCol_;		// ������(����, ��, ...) �浹ü���
	
	std::vector<InventoryTileBox*> InvStoreInfo_;		// ������ �������
	std::vector<GameEngineCollision*> InvStoreCol_;		// ������ �浹ü ���

private:
	std::vector<ItemInfo> InvBatchItemList_;			// �κ�â�� ��ġ�Ǿ��ִ� ���������� ���
#pragma endregion

#pragma region �κ�â ���/�ϴ� ��ġ�� ������
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
	void EquipTileBoxClick(GameEngineCollision* _Other, int _Index);	// �浹�� Ÿ���� �ε����� �޾ƿ´�.
	void StoreTileBoxClick(GameEngineCollision* _Other, int _Index);	// �浹�� Ÿ���� �ε����� �޾ƿ´�.

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetInventoryBoxTileActvie();
	void SetInentroyBoxTileInactive();

public: // �κ�â �ʱ����
	void InitInventoryView();
	void CreateInvTile();
	void CreateInvTileInfo();
	void CreateInvTileCol();
	void PlayerItemListBatch();
	
public: // �κ�â ������ ��ġ/����/�̵�
	void ItemBatchOn(int _TileIndex, InvTabType _InvTabType);
	void ItemBatchOff(int _TileIndex, InvTabType _InvTabType);


public: // 
	
};


#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "MainPlayerInfomation.h"

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
class InventoryView : public GameEngineActor
{
#pragma region �κ�â ����������
	class ItemInfo
	{
	private:
		int Index_;								// ������������Ͽ����� �ε���
		ItemLocType CurItemLoc_;				// �ش� �������� ��ġ ��ġ
		std::vector<int> ItemArrIndexs_;		// ��ġ��ġ�� NORMAL�̶�� �������� �����ϴ� Ÿ���ε������
		
	private:
		std::string ItemTextureName_;			// ������ �ؽ��ĸ� 
		std::string ItemName_;					// �����۸�
		int ItemCode_;							// �������ڵ�
		float4 ItemScale_;						// �����۷����� ũ��

	private:
		GameEngineUIRenderer* ItemRenderer_;	// ������ ������
		GameEngineCollision* ItemCollision_;	// ������ �浹ü

	public:
		// ������ ���� ����
		bool CreateItemInfo(int _Index, ItemLocType _LocType, const std::string& _ItemName_);

	public:	
		// �ϴ� �����ǿ� ��ġ�Ǵ� �������̸�, �������� �����ϴ� Ÿ���� �ε����� 1�� �ƴ� �������� 
		// ������ �����ϴ� Ÿ���� �ε����� ��� �˰��ִ´�.
		void SetItemArrIndexs(std::vector<int> _TileIndex);
	};

#pragma endregion

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
	std::vector<ItemInfo*> InvArrItemList_;				// �κ�â�� ��ġ�Ǿ��ִ� ���������� ���
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
	void PlayerItemListArrangement();
	
public: // �κ�â ������ ��ġ/����/�̵�
	void ItemArrangementOn(int _TileIndex, InvTabType _InvTabType);
	void ItemArrangementOff(int _TileIndex, InvTabType _InvTabType);


public: // 
	
};


#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "MainPlayerInfomation.h"

// �з� : 
// �뵵 : 
// ���� : 
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

private: // �κ��丮 ����
	std::vector<InventoryTileBox*> NormalInventoryTile_;		// �κ��丮â �ϴ� �ڽ�(���������۸��Ÿ�Ϲڽ����)
	std::vector<InventoryTileBox*> PlayerEquipInvTile_;			// �κ��丮â ��� �ڽ�(�÷��̾� ������ Ÿ�Ϲڽ����)
	
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


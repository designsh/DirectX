#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

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
#pragma endregion

#pragma region �κ�â ��� ����������
private:
	std::vector<InventoryTileBox*> InvEquipInfo_;



#pragma endregion

#pragma region �κ�â �ϴ� ����������
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

public: // �κ�â �ʱ����
	void InitInventoryView();

public: // 


public: // 
	
};


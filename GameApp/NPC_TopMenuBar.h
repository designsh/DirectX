#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "AllNPCInfomation.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class NPC_BuySellView;
class NPC_TopMenuBar : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* TopMenuPanel_;
	GameEngineCollision* TopMenuPanelCol_;

private:
	// ��ȭ
	GameEngineUIRenderer* ConversationMenuRenderer_;
	GameEngineCollision* ConversationMenuCol_;

	// �Ǹ�â
	GameEngineUIRenderer* BuySellMenuRenderer_;
	GameEngineCollision* ButSellMenuCol_;

	// ���
	GameEngineUIRenderer* CloseMenuRenderer_;
	GameEngineCollision* CloseMenuCol_;

private:
	Button_State ConversationMenuBtnState_;
	Button_State BuySellMenuBtnState_;
	Button_State CloseMenuBtnState_;
private:
	NPCClassType NPCClassType_;
	NPCType NPCType_;

private:
	NPC_BuySellView* BuySellView_;

public:
	NPC_TopMenuBar();
	~NPC_TopMenuBar();

protected:		// delete constructer
	NPC_TopMenuBar(const NPC_TopMenuBar& _other) = delete;
	NPC_TopMenuBar(NPC_TopMenuBar&& _other) noexcept = delete;

private:		//delete operator
	NPC_TopMenuBar& operator=(const NPC_TopMenuBar& _other) = delete;
	NPC_TopMenuBar& operator=(const NPC_TopMenuBar&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void SelectConversationMenu(GameEngineCollision* _Other);
	void SelectBuySellMenu(GameEngineCollision* _Other);
	void SelectCloseMenu(GameEngineCollision* _Other);

public:
	inline NPC_BuySellView* GetBuySellView()
	{
		return BuySellView_;
	}

public:
	void CreateNPCTopMenu(NPCClassType _NPCClassType, NPCType _NPCType);

public: // �޴� Ȱ��ȭ �� ��ġ������
	void NPCTopMenuActive();

public:
	void MenuButtonStateReset();
};


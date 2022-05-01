#pragma once

// UI Widget Button State
enum class Button_State
{
	Normal,		// �⺻����
	MouseOn,	// Mouse Over(��ư���� ���콺Ŀ���� �ö����)
	Click,		// Click
	Disabled,	// ��Ȱ������
	End
};

// Update Order
enum class UpdateOrder
{
	PLAYER,
	MONSTER,
	NPC,
	OBJECT,
};

// UI���� ��������
enum class UIRenderOrder
{
	NPCUI0,
	NPCUI0_Tab,
	NPCUI0_Button,
	NPCUI0_Collider,
	NPCUI0_Text,
	NPCUI0_TextCol,
	NPCUI1,
	NPCUI1_Tab,
	NPCUI1_Button,
	NPCUI1_Collider,
	NPCUI1_Text,
	NPCUI1_TextCol,
	UI0,
	UI0_Tab,
	UI0_Button,
	UI0_Render,
	UI0_Collider,
	UI0_Text,
	UI0_TextCol,
	UI1,
	UI1_Tab,
	UI1_Button,
	UI1_Render,
	UI1_Collider,
	UI1_Text,
	UI1_TextCol,
	UI2,
	UI2_Collider,
	UI2_Text,
	UI3,
	UI3_Collider,
	UI3_Text,
	UI4,
	UI4_Collider,
	UI4_Text,
	UI5,
	UI5_Collider,
	UI5_Text,
	UI6,
	UI6_Collider,
	UI6_Text,
	UI7,
	UI7_Collider,
	UI7_Text,
	UI8,
	UI8_Collider,
	UI8_Text,
	UI9,
	UI9_Collider,
	UI9_Text,
	UI10,
	UI10_Collider,
	UI10_Text,
	UI11,
	UI11_Collider,
	UI11_Text,
	UI12,
	UI12_Collider,
	UI12_Text,
	UIMoveabledCheckCol,	// �÷��̾� �̵��Ұ� ���� �浹ü
	Popup,					// �˾���(�����޼��� or ���ֱ�/�������˾�)
	Popup_Action_Col,		// �˾��� �浹ü(���콺 �ٸ� ���� ����)
	Popup_Button,
	Popup_Collider,
	Popup_Text,
	Object,
	Monster,
	Player = 8888,
	Mouse = 9999,
	MouseHoldItem,
	MAX
};

// ���̹����� z�� ����
enum class DepthZOrder
{
	Object,
	Monster,
	PlayerObject_Effect,
	PlayerObject,
	Player,
	MapObject,
	Map,
	BackDrop,
	MAX
};

// UI ProgressBar Direct
enum class ProgressBarDirect
{
	BottomToTop,		// Bottom -> Top
	TopToBottom,		// Top -> Bottom
	RightToLeft,		// Right -> Left
	LeftToRight			// Left -> Right
};

// UI SkillPageNo : SkillInfomation�� ����
enum class SkillPageNo
{
	NONE = -1,
	CurseSpell,			// Page1
	PoisonandBoneSpells,// Page2
	SummonSpell,		// Page3
	MAX
};


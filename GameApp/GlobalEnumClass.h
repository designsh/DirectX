#pragma once

// UI Widget Button State
enum class Button_State
{
	Normal,		// 기본상태
	MouseOn,	// Mouse Over(버튼위에 마우스커서가 올라오면)
	Click,		// Click
	Disabled,	// 비활성상태
	End
};

// UI전용 렌더오더
enum class UIRenderOrder
{
	UI0,
	UI0_Tab,
	UI0_Button,
	UI0_Collider,
	UI0_Text,
	UI1,
	UI1_Collider,
	UI1_Text,
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
	ErrorPopup,
	ErrorPopup_Button,
	ErrorPopup_Collider,
	ErrorPopup_Text,
	Mouse = 9999,
	MAX
};

// 깊이버퍼의 z값 오더
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

// UI SkillPageNo : SkillInfomation과 동일
enum class SkillPageNo
{
	NONE = -1,
	CurseSpell,			// Page1
	PoisonandBoneSpells,// Page2
	SummonSpell,		// Page3
	MAX
};


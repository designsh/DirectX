#pragma once

// UI전용 렌더오더
enum class UIRenderOrder
{
	UI0,
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

// 플레이어 z값 오더
enum class PlayerZOrder
{

};

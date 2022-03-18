#pragma once

// UI���� ��������
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

// �÷��̾� z�� ����
enum class PlayerZOrder
{

};

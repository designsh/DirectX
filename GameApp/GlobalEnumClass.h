#pragma once

enum class UpdateOrder
{
	Map,
	MapObject,
	NormalObject,
	Player,
	Monster,
	UI,
	Mouse
};

enum class OrderGroup
{
	Map,
	MapObject0,
	MapObject1,
	MapObject2,
	MapObject3,
	NormalObject0,
	NormalObject1,
	NormalObject2,
	NormalObject3,
	Player,
	PlayerAttack,
	PlayerSkill,
	PlayerUI0,
	PlayerUI1,
	PlayerUI2,
	PlayerUI3,
	Monster,
	MonsterAttack,
	MonsterSkill,
	MonsterUI0,
	MonsterUI1,
	MonsterUI2,
	MonsterUI3,
	UI0,
	UI1,
	UI2,
	UI3,
	Mouse,
	MouseCollider,
	MAX
};


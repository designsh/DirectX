#pragma once
#include "FixedTileMap_Common.h"

// ·£´ý¸Ê °øÅë Á¤º¸ Çì´õ

class Dungeon
{
private:	// member Var
	Dungeon* Left_;
	Dungeon* Right_;
	Dungeon* Parent_;
	float4 DungeonSize_;
	float4 RoomSize_;

public:
	Dungeon(int _X, int _Y, int _Width, int _Height)
	{

	}

	~Dungeon()
	{

	}
};

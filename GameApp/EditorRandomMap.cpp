#include "PreCompile.h"
#include "EditorRandomMap.h"

bool EditorRandomMap::FirstRandomLoad_ = false;
std::vector<int> EditorRandomMap::IgnoreRange;
std::vector<std::vector<float4>> EditorRandomMap::RandomRange;
std::vector<std::vector<int>> EditorRandomMap::RandomReversRange;
std::vector<std::vector<int>> EditorRandomMap::RandomNextRange;

EditorRandomMap::EditorRandomMap()
{
}

EditorRandomMap::~EditorRandomMap()
{
}

void EditorRandomMap::Start()
{
	RandomStartPos_.clear();
	RandomStartPos_ = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };

	IgnoreRange.resize(4);
	RandomNextRange.resize(4);
	RandomRange = { {float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN},
					{float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN},
					{float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN},
					{float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN}, };
	RandomReversRange = { {1, 0, 3, 2},
						  {1, 0, 3, 2},
						  {1, 0, 3, 2},
						  {1, 0, 3, 2}, };
}


void EditorRandomMap::RandomRoad(int _Count, bool _Multidirectional)
{
	//if (false == _Multidirectional) // 한방향 랜덤 로드(길) 생성
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		if (i == IgnoreRange[0])
	//		{
	//			continue;
	//		}

	//		RandomNextRange[0].push_back(i);
	//	}

	//	int DirIndex = RandomNextRange[0][Random_.RandomInt(0, static_cast<int>(RandomNextRange[0].size()) - 1)];

	//	float4 Dir = RandomRange[0][DirIndex];

	//	for (size_t i = 0; i < _Count; i++)
	//	{
	//		SetFloorTile(TileIndex{ RandomStartPos_[0].ix(), RandomStartPos_[0].iy() }, 0);
	//		RandomStartPos_[0] += Dir;
	//	}

	//	IgnoreRange[0] = RandomReversRange[0][DirIndex];
	//	RandomNextRange[0].clear();
	//}
	//else // 다방향 랜덤 로드(길) 생성
	//{
	//	if (false == FirstRandomLoad_)
	//	{
	//		// 최초 생성 Flag On
	//		FirstRandomLoad_ = true;

	//		// 최초 생성되었으므로 최대 4방향 랜덤 로드 생성
	//		for (int i = 0; i < 4; ++i)
	//		{
	//			RandomNextRange[i].push_back(i);
	//		}

	//		std::vector<int> DirIndex = { {-1}, {-1}, {-1}, {-1}, };
	//		std::vector<float4> Dir = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };

	//		for (int i = 0; i < 4; ++i)
	//		{
	//			DirIndex[i] = RandomNextRange[i][Random_.RandomInt(0, static_cast<int>(RandomNextRange[i].size()) - 1)];
	//			Dir[i] = RandomRange[i][DirIndex[i]];
	//			SetFloorTile(TileIndex{ RandomStartPos_[i].ix(), RandomStartPos_[i].iy() }, 0);
	//			RandomStartPos_[i] += Dir[i];
	//		}

	//		for (int i = 0; i < 4; ++i)
	//		{
	//			IgnoreRange[i] = RandomReversRange[i][DirIndex[i]];
	//			RandomNextRange[i].clear();
	//		}

	//		DirIndex.clear();
	//		Dir.clear();
	//	}
	//	else
	//	{
	//		// 최대 3방향 랜덤 로드 생성
	//		for (int i = 0; i < 4; ++i)
	//		{
	//			for (int j = 0; j < 3; j++)
	//			{
	//				if (j == IgnoreRange[i])
	//				{
	//					continue;
	//				}

	//				RandomNextRange[i].push_back(j);
	//			}
	//		}

	//		std::vector<int> DirIndex = { {-1}, {-1}, {-1}, {-1}, };
	//		std::vector<float4> Dir = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };

	//		for (int i = 0; i < 4; ++i)
	//		{
	//			DirIndex[i] = RandomNextRange[i][Random_.RandomInt(0, static_cast<int>(RandomNextRange[i].size()) - 1)];
	//			Dir[i] = RandomRange[i][DirIndex[i]];
	//			SetFloorTile(TileIndex{ RandomStartPos_[i].ix(), RandomStartPos_[i].iy() }, 0);
	//			RandomStartPos_[i] += Dir[i];

	//			IgnoreRange[i] = RandomReversRange[i][DirIndex[i]];
	//			RandomNextRange[i].clear();
	//		}

	//		DirIndex.clear();
	//		Dir.clear();
	//	}
	//}
}


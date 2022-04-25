#pragma once

// 해당 맵의 벽정보와 오브젝트정보를 이용하여 생성
// 벽정보의 WALL,NONE 타입이면 이동불가지역으로 판단
// 오브젝트정보의 OBJECT,NONE 타입이면 이동불가지역으로 판단
enum class NavigationType
{
	NONE = -1,	// 수집실패
	NOR,		// 이동가능지역
	WALL,		// 이동불가지역
};

// 노드체크 방향(체크하려는 이웃노드)
enum Neighbor_Dir
{
	ND_Top,
	ND_RightTop,
	ND_Right,
	ND_RightBottom,
	ND_Bottom,
	ND_LeftBottom,
	ND_Left,
	ND_LeftTop,
	ND_End
};

// 네비게이션 정보 타입
enum class Nav_Insert_Type
{
	None,
	Open,
	Close
};

// 네비게이션 정보(노드정보)
struct NavNodeInfo
{
	Nav_Insert_Type NavType;	// 열린노드/닫힌노드
	int	IndexX;
	int	IndexY;
	float Cost;
	float Dist;

	NavNodeInfo()
	{
		Cost = 0.f;
		Dist = 0.f;
		IndexX = -1;
		IndexY = -1;
		NavType = Nav_Insert_Type::None;
	}

	void Clear()
	{
		Cost = 0.f;
		Dist = 0.f;
		NavType = Nav_Insert_Type::None;
	}
};

// 네비게이션 관리자
struct NavNodeInfoManager
{
	std::vector<NavNodeInfo> vecNavInfo;
	std::vector<NavNodeInfo*> vecOpen;
	std::vector<NavNodeInfo*> vecUse;
	int OpenCount;
	int	UseCount;
	int	CountX;
	int	CountY;

	NavNodeInfo* GetNavInfo(int _IndexX, int _IndexY)
	{
		if (_IndexX < 0 || _IndexY < 0 || _IndexX >= CountX || _IndexY >= CountY)
		{
			return nullptr;
		}

		return &vecNavInfo[_IndexY * CountX + _IndexX];
	}

	NavNodeInfoManager()
	{
		OpenCount = 0;
		UseCount = 0;
		CountX = 0;
		CountY = 0;
	}
};

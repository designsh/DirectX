#include "PreCompile.h"
#include "Navigation2D.h"

bool Navigation2D::SortOpenList(NavNodeInfo* _Src, NavNodeInfo* _Dest)
{
	return false;
}

Navigation2D::Navigation2D() :
	NavRenderer_(nullptr),
	NavInfoManager_(nullptr)
{
}

Navigation2D::~Navigation2D()
{
}

bool Navigation2D::FindNode(NavNodeInfo* _Node, NavNodeInfo* _GoalNode, const float4& _Goal, std::vector<float4>& _vecPath)
{
	return false;
}

bool Navigation2D::FindPath(const float4& _Start, const float4& _Goal, std::vector<float4>& _vecPath)
{




	return false;
}

#include "PreCompile.h"
#include "GameEnginePathFind.h"

GameEnginePathFind::GameEnginePathFind() :
	PoolCount_(0)
{
}

GameEnginePathFind::~GameEnginePathFind()
{
}

std::list<PathIndex> GameEnginePathFind::CalReturn(AStarNode* _EndNode)
{
	std::list<PathIndex> ReturnList;

	while (nullptr != _EndNode->Parent_)
	{
		ReturnList.push_front(_EndNode->Index_);
	}
	return ReturnList;
}

AStarNode* GameEnginePathFind::CreateNode(PathIndex _Index, PathIndex End, AStarNode* _ParentNode)
{
	if (PoolCount_ >= NodePool_.size())
	{
		return nullptr;
	}

	AStarNode* NewNode = &NodePool_[PoolCount_++];
	NewNode->Parent_ = _ParentNode;
	NewNode->Reset();
	NewNode->Index_ = _Index;
	NewNode->CalLen(End);
	return NewNode;
}

std::list<PathIndex> GameEnginePathFind::AStarFind4Way(PathIndex _Start, PathIndex _End, std::function<bool(PathIndex)> _OpenFunction, int _Maximum)
{
	PathIndex ArrDir[4] = { {1, 0 }, {-1, 0}, {0, 1}, {0, -1} };

	// Clear
	PoolCount_ = 0;
	NodePool_.resize(_Maximum);
	OpenList_.clear();
	OpenKeys_.clear();
	CloseList_.clear();
	CloseKeys_.clear();

	// 시작노드 결정
	AStarNode* NewNode = CreateNode(_Start, _End, nullptr);
	OpenList_.insert(std::make_pair(NewNode->TotalLen_, NewNode));
	OpenKeys_.insert(NewNode->Index_.Index_);

	// 경로탐색 시작
	while (0 != OpenList_.size())
	{
		// 메모리 최대치 탐색이 일어났다면 경로를 찾지못함
		if (PoolCount_ >= NodePool_.size())
		{
			return std::list<PathIndex>();
		}

		// 열린노드 목록에서 시작노드를 Get
		AStarNode* FirstNode = OpenList_.begin()->second;

		// 열린노드 목록에서 해당 노드를 삭제
		OpenList_.erase(OpenList_.begin());
		OpenKeys_.erase(FirstNode->Index_.Index_);

		// 닫힌노드 목록에 해당 노드 추가
		CloseList_.push_back(FirstNode);
		CloseKeys_.insert(FirstNode->Index_.Index_);

		// 해당 노드의 4방향 이웃노드들을 체크
		for (size_t i = 0; i < 4; i++)
		{
			PathIndex FindIndex = FirstNode->Index_ + ArrDir[i];

			// 열린노드목록에 해당 노드가 존재하면 continue
			if (OpenKeys_.end() != OpenKeys_.find(FindIndex.Index_))
			{
				continue;
			}

			// 닫힌노드목록에 해당 노드가 존재하면 continue
			if (CloseKeys_.end() != CloseKeys_.find(FindIndex.Index_))
			{
				continue;
			}

			// 사용자조건에 의하여 이동불가지역이라면 continue
			if (true == _OpenFunction(FindIndex))
			{
				continue;
			}

			// 모든 조건을 만족하여 이동가능 경로라면
			// 시작노드의 이웃하는 노드이므로 시작노드가 부모노드로 결정
			AStarNode* NewNode = CreateNode(_Start, _End, FirstNode);

			// 목표 노드에 도착했다면 이동경로 반환
			if (_End == FindIndex)
			{
				return CalReturn(NewNode);
			}

			// 아니라면 열린노드목록에 해당 노드 추가
			OpenList_.insert(std::make_pair(NewNode->TotalLen_, NewNode));
			OpenKeys_.insert(FirstNode->Index_.Index_);
		}
	}

	return std::list<PathIndex>();
}

std::list<PathIndex> GameEnginePathFind::AStarFind8Way(PathIndex Start, PathIndex End, std::function<bool(PathIndex)> _OpenFunction, int _Maximum)
{
	return std::list<PathIndex>();
}

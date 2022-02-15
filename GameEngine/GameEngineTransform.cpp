#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() :
	TransData_{},
	Parent_(nullptr)	
{
}

GameEngineTransform::~GameEngineTransform()
{

}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	if (nullptr == _Parent)
	{

	}
	else
	{
		Parent_->DetachChild(this);
	}
	
	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
	// 현재 트랜스폼의 부모를 교체




}

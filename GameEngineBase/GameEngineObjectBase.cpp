#include "PreCompile.h"
#include "GameEngineObjectBase.h"

GameEngineObjectBase::GameEngineObjectBase() // default constructer 디폴트 생성자
	: isDeath_(false),
	isUpdate_(true),
	isDebug_(false), // 디버깅 기능 이거 true로 해놓고 f9 걸어 놓으면 
	parent_(nullptr)
{

}

GameEngineObjectBase::~GameEngineObjectBase() // default destructer 디폴트 소멸자
{

}

GameEngineObjectBase::GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: isDeath_(_other.isDeath_),
	isUpdate_(_other.isUpdate_),
	isDebug_(_other.isDebug_), // 디버깅 기능 이거 true로 해놓고 f9 걸어 놓으면 
	parent_(_other.parent_)
{

}


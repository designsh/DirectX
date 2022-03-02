#include "PreCompile.h"
#include "CoffinObject.h"

#include <GameEngine/GameEngineImageRenderer.h>

CoffinObject::CoffinObject() :
	Coffin_(nullptr),
	CoffinType_(0),
	AnimationStart_(false)
{
}

CoffinObject::~CoffinObject()
{
}

void CoffinObject::Start()
{
}

void CoffinObject::Update(float _DeltaTime)
{
}

void CoffinObject::SetCoffinType(int _CoffinType)
{
	CoffinType_ = _CoffinType;
}

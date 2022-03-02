#include "PreCompile.h"
#include "BoxObject.h"

#include <GameEngine/GameEngineImageRenderer.h>

BoxObject::BoxObject() :
	BoxObject_(nullptr),
	BoxType_(0),
	AnimationStart_(false)
{
}

BoxObject::~BoxObject()
{
}

void BoxObject::Start()
{
}

void BoxObject::Update(float _DeltaTime)
{
}

void BoxObject::SetBoxType(int _BoxType)
{
	BoxType_ = _BoxType;
}

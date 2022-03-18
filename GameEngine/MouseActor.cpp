#include "PreCompile.h"
#include "MouseActor.h"
#include <GameEngine\GameEngineInput.h>

MouseActor::MouseActor() :
	UIRenderer_(nullptr)
{
}

MouseActor::~MouseActor()
{
}

void MouseActor::Start()
{
	UIRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
	UIRenderer_->GetTransform()->SetLocalScaling({ 50.0f, 50.0f });
	UIRenderer_->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());
}

void MouseActor::Update(float _DeltaTime)
{
	GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
}

void MouseActor::SetCurSor(std::string _Name)
{
	UIRenderer_->SetImage(_Name);
}

void MouseActor::SetCurSor(std::string _Name, int _Index)
{
	UIRenderer_->SetImage(_Name);
	UIRenderer_->SetIndex(_Index);
}

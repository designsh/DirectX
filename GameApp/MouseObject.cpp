#include "PreCompile.h"
#include "MouseObject.h"

#include "GlobalEnumClass.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

MouseObject::MouseObject() :
	Mouse_(nullptr),
	MouseCollider_(nullptr),
	State_(MouseState::Stay)
{
}

MouseObject::~MouseObject()
{
}

void MouseObject::Start()
{
	// 이미지 편집 후 적용예정
	GameEngineTexture* MouseStay = GameEngineTextureManager::GetInst().Find("Mouse.png");
	MouseStay->Cut(8, 1);

	Mouse_ = CreateTransformComponent<GameEngineImageRenderer>(static_cast<int>(OrderGroup::Mouse));
	Mouse_->CreateAnimation("Mouse.png", "StayState", 0, 7, 0.1f);
	Mouse_->CreateAnimation("Mouse.png", "MoveState", 0, 0, 0.1f, false);
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->SetChangeAnimation("StayState");

	MouseCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(OrderGroup::MouseCollider));
	MouseCollider_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
}

void MouseObject::Update(float _DeltaTime)
{
	float4 PrevPos = GameEngineInput::GetInst().GetPrevMousePos();
	float4 CurPos = GameEngineInput::GetInst().GetMousePos();

	// 마우스 위치 갱신
	GetTransform()->SetLocalPosition(CurPos);

	// 이전 마우스위치와 현재마우스가 달라졌을때 동작상태에서 대기상태로 전환
	if (PrevPos == CurPos)
	{
		// 마우스상태가 동작상태였다면
		if (State_ == MouseState::Move)
		{
			// 대기상태로 전환 후
			Mouse_->SetChangeAnimation("StayState");

			// 현재 마우스 상태 저장
			State_ = MouseState::Stay;
		}
	}
	else
	{
		// 마우스상태가 대기상태였다면
		if (State_ == MouseState::Stay)
		{
			// 동작상태로 전환 후
			Mouse_->SetChangeAnimation("MoveState");

			// 현재 마우스 상태 저장
			State_ = MouseState::Move;
		}
	}
}

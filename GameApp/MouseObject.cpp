#include "PreCompile.h"
#include "MouseObject.h"

#include "GlobalEnumClass.h"

#include <GameEngine/GameEngineUIRenderer.h>
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
	// �̹��� ���� �� ���뿹��
	GameEngineTexture* MouseStay = GameEngineTextureManager::GetInst().Find("Mouse.png");
	MouseStay->Cut(8, 1);

	Mouse_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(OrderGroup::Mouse));
	Mouse_->CreateAnimation("Mouse.png", "StayState", 0, 7, 0.4f);
	Mouse_->CreateAnimation("Mouse.png", "MoveState", 0, 0, 0.1f, false);
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->SetChangeAnimation("StayState");

	MouseCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(OrderGroup::MouseCollider));
	MouseCollider_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));

	// 220315 �׽�Ʈ ���Ǹ� ���� �ӽ��ּ�
	//ShowCursor(FALSE);
}

void MouseObject::Update(float _DeltaTime)
{
	float4 PrevPos = GameEngineInput::GetInst().GetPrevMouse3DPos();
	float4 CurPos = GameEngineInput::GetInst().GetMouse3DPos();

	// ���콺 ��ġ ����
	GetTransform()->SetLocalPosition(CurPos);

	// ���� ���콺��ġ�� ���縶�콺�� �޶������� ���ۻ��¿��� �����·� ��ȯ
	if (PrevPos == CurPos)
	{
		// ���콺���°� ���ۻ��¿��ٸ�
		if (State_ == MouseState::Move)
		{
			// �����·� ��ȯ ��
			Mouse_->SetChangeAnimation("StayState");

			// ���� ���콺 ���� ����
			State_ = MouseState::Stay;
		}
	}
	else if(PrevPos.x != CurPos.x || PrevPos.y != CurPos.y)
	{
		// ���콺���°� �����¿��ٸ�
		if (State_ == MouseState::Stay)
		{
			// ���ۻ��·� ��ȯ ��
			Mouse_->SetChangeAnimation("MoveState");

			// ���� ���콺 ���� ����
			State_ = MouseState::Move;
		}
	}
}

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
	GameEngineTexture* MouseStay = GameEngineTextureManager::GetInst().Find("Mouse.png");
	MouseStay->Cut(8, 1);

	Mouse_ = CreateTransformComponent<GameEngineUIRenderer>();
	Mouse_->CreateAnimation("Mouse.png", "StayState", 0, 7, 0.4f);
	Mouse_->CreateAnimation("Mouse.png", "MoveState", 0, 0, 0.1f, false);
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));
	Mouse_->SetRenderGroup(static_cast<int>(UIRenderOrder::Mouse));
	Mouse_->SetChangeAnimation("StayState");

	float4 PivotPos = Mouse_->GetTransform()->GetLocalPosition();

	MouseCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Mouse));
	MouseCollider_->GetTransform()->SetLocalScaling(float4(5.f, 5.f, 1.f));

	// 220329 SJH : �׽�Ʈ������ �ӽ��ּ�
	//GameEngineInput::GetInst().HideCursor();
}

void MouseObject::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(MouseCollider_->GetTransform(), CollisionType::Rect);

	float4 PrevPos = GameEngineInput::GetInst().GetPrevMouse3DPos();
	float4 CurPos = GameEngineInput::GetInst().GetMouse3DPos();

	// ���콺 ��ġ ����
	GetTransform()->SetLocalPosition(float4(CurPos.x, CurPos.y));

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

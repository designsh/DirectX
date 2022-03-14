#include "PreCompile.h"
#include "MouseObject.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

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
	//// �̹��� ���� �� ���뿹��
	////GameEngineTexture* MouseStay = GameEngineTextureManager::GetInst().Find("MouseStay.png");
	////MouseStay->Cut(8, 1);

	//// TEST
	//Mouse_ = CreateTransformComponent<GameEngineImageRenderer>(static_cast<int>(OrderGroup::Mouse));
	//Mouse_->SetImage("Mouse_Texture.png");
	//Mouse_->CreateAnimation("StayState", 0, 7, 0.1f);
	//Mouse_->CreateAnimation("MoveState", 0, 0, 0.1f, false);
	//Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	//Mouse_->SetChangeAnimation("StayState");

	//MouseCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(OrderGroup::MouseCollider));
	//MouseCollider_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
}

void MouseObject::Update(float _DeltaTime)
{
	//float4 PrevPos = GameEngineInput::GetInst().GetPrevMousePos();
	//float4 CurPos = GameEngineInput::GetInst().GetMousePos();

	//// ���콺 ��ġ ����
	////GetTransform()->SetLocalPosition(float4());

	//// ���� ���콺��ġ�� ���縶�콺�� �޶������� ���ۻ��¿��� �����·� ��ȯ
	//if (PrevPos == CurPos)
	//{
	//	// ���콺���°� ���ۻ��¿��ٸ�
	//	if (State_ == MouseState::Move)
	//	{
	//		// �����·� ��ȯ ��
	//		Mouse_->SetChangeAnimation("StayState");

	//		// ���� ���콺 ���� ����
	//		State_ = MouseState::Stay;
	//	}
	//}
	//else
	//{
	//	// ���콺���°� �����¿��ٸ�
	//	if (State_ == MouseState::Stay)
	//	{
	//		// ���ۻ��·� ��ȯ ��
	//		Mouse_->SetChangeAnimation("MoveState");

	//		// ���� ���콺 ���� ����
	//		State_ = MouseState::Move;
	//	}
	//}
}

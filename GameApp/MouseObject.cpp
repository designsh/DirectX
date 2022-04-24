#include "PreCompile.h"
#include "MouseObject.h"

#include "GlobalEnumClass.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

MouseObject::MouseObject() :
	IsItemHold_(false),
	HoldItemName_(),
	ItemRenderer_(nullptr),
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

	// Ư����� Ŀ��
	GameEngineTexture* MouseBuy = GameEngineTextureManager::GetInst().Find("BuyCursor.png");
	MouseBuy->Cut(1, 1);
	GameEngineTexture* MouseSell = GameEngineTextureManager::GetInst().Find("SellCursor.png");
	MouseSell->Cut(1, 1);
	GameEngineTexture* MouseRepair = GameEngineTextureManager::GetInst().Find("RepairCursor.png");
	MouseRepair->Cut(1, 1);

	Mouse_ = CreateTransformComponent<GameEngineUIRenderer>();
	Mouse_->CreateAnimation("Mouse.png", "StayState", 0, 7, 0.4f);
	Mouse_->CreateAnimation("Mouse.png", "MoveState", 0, 0, 0.1f, false);

	// Ư����ɿ����� Ŀ�� �ִϸ��̼�
	Mouse_->CreateAnimation("BuyCursor.png", "BuyState", 0, 0, 0.1f, false);			// ���Ź�ưŬ���� Ȱ��ȭ
	Mouse_->CreateAnimation("SellCursor.png", "SellState", 0, 0, 0.1f, false);			// �ǸŹ�ưŬ���� Ȱ��ȭ
	Mouse_->CreateAnimation("RepairCursor.png", "RepairState", 0, 0, 0.1f, false);		// ������ưŬ���� Ȱ��ȭ

	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));
	Mouse_->SetRenderGroup(static_cast<int>(UIRenderOrder::Mouse));
	Mouse_->SetChangeAnimation("StayState");

	MouseCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Mouse));
	MouseCollider_->GetTransform()->SetLocalScaling(float4(5.f, 5.f, 1.f));

	// ������ ��� ������
	ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::MouseHoldItem));
	ItemRenderer_->Off();

	// Ŀ�� Off : 220404 SJH �׽�Ʈ�� ���� �ӽ��ּ�
	//GameEngineInput::GetInst().CursorHide();
}

void MouseObject::Update(float _DeltaTime)
{
	float4 PrevPos = GameEngineInput::GetInst().GetPrevMouse3DPos();
	float4 CurPos = GameEngineInput::GetInst().GetMouse3DPos();

	// ���콺 ��ġ ����
	GetTransform()->SetWorldPosition(float4(CurPos.x, CurPos.y));

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

#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(MouseCollider_->GetTransform(), CollisionType::Rect);
	//GetLevel()->PushDebugRender(MouseCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG
}

void MouseObject::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// Ÿ��Ʋ ȭ�� or �ε�ȭ�� or ĳ���ͻ���ȭ�� or ĳ���ͼ���ȭ�� or ����ȭ�� �̵��� �����̵�����
	if (std::string::npos != _NextLevel->GetName().find("TitleLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("CreateCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("SelectCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("LoadingLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("MapEditorLevel"))
	{
		return;
	}

	// ���콺 �������� ����
	GetLevel()->SetLevelActorMove(_NextLevel, this);
}

void MouseObject::ItemHold(const std::string& _ItemName, const float4& _ItemSize)
{
	// �������� �������
	IsItemHold_ = true;

	// �κ��丮â or â�� or �Ǹ�â���� ���콺 Ŭ������ �������� ������� ȣ��
	HoldItemName_ = _ItemName;

	// ���콺 Ŀ�������� Off
	Mouse_->Off();

	// ������ ������ On
	ItemRenderer_->SetImage(HoldItemName_);

	// ������ �ǹ���ġ ���
	ItemRenderer_->GetTransform()->SetLocalScaling(_ItemSize);
	ItemRenderer_->On();
}

void MouseObject::ItemPutDown()
{
	// �������� ������
	IsItemHold_ = false;
	HoldItemName_ = "";

	// ���콺 Ŀ�������� On
	Mouse_->On();

	// �����۷����� Off
	ItemRenderer_->Off();
}

void MouseObject::BuyCursorActive()
{
	// Ŀ�� �ִϸ��̼� ����
	Mouse_->SetChangeAnimation("BuyState");
	Mouse_->GetTransform()->SetLocalScaling(float4(32.f, 40.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(14.5f, -22.5f));

	// ���� ���콺���� ����
	State_ = MouseState::Buy;
}

void MouseObject::BuyCursorInActive()
{
	// Ŀ�� �ִϸ��̼� ����
	Mouse_->SetChangeAnimation("StayState");
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));

	// ���� ���콺���� ����
	State_ = MouseState::Stay;
}

void MouseObject::SellCursorActive()
{
	// Ŀ�� �ִϸ��̼� ����
	Mouse_->SetChangeAnimation("SellState");
	Mouse_->GetTransform()->SetLocalScaling(float4(32.f, 40.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(14.5f, -22.5f));

	// ���� ���콺���� ����
	State_ = MouseState::Sell;
}

void MouseObject::SellCursorInactive()
{
	// Ŀ�� �ִϸ��̼� ����
	Mouse_->SetChangeAnimation("StayState");
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));

	// ���� ���콺���� ����
	State_ = MouseState::Stay;
}

void MouseObject::RepairCursorActive()
{
	// Ŀ�� �ִϸ��̼� ����
	Mouse_->SetChangeAnimation("RepairState");
	Mouse_->GetTransform()->SetLocalScaling(float4(32.f, 40.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(14.5f, -22.5f));

	// ���� ���콺���� ����
	State_ = MouseState::Repair;
}

void MouseObject::RepairCursorInactive()
{
	// Ŀ�� �ִϸ��̼� ����
	Mouse_->SetChangeAnimation("StayState");
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));

	// ���� ���콺���� ����
	State_ = MouseState::Stay;
}

void MouseObject::CursorStateReset()
{
	// Ŀ�� �ִϸ��̼� ����
	Mouse_->SetChangeAnimation("StayState");
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));

	// ���� ���콺���� ����
	State_ = MouseState::Stay;
}

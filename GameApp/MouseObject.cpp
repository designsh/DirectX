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

	// 아이템 들기 렌더러
	ItemRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::MouseHoldItem));
	ItemRenderer_->Off();

	// 커서 Off : 220404 SJH 테스트를 위한 임시주석
	//GameEngineInput::GetInst().CursorHide();
}

void MouseObject::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(MouseCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	float4 PrevPos = GameEngineInput::GetInst().GetPrevMouse3DPos();
	float4 CurPos = GameEngineInput::GetInst().GetMouse3DPos();

	// 마우스 위치 갱신
	GetTransform()->SetLocalPosition(float4(CurPos.x, CurPos.y));

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
	else if(PrevPos.x != CurPos.x || PrevPos.y != CurPos.y)
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

void MouseObject::ItemHold(const std::string& _ItemName, const float4& _ItemSize)
{
	// 아이템을 들고있음
	IsItemHold_ = true;

	// 인벤토리창 or 창고 or 판매창에서 마우스 클릭으로 아이템을 들었을때 호출
	HoldItemName_ = _ItemName;

	// 마우스 커서렌더러 Off
	Mouse_->Off();

	// 아이템 렌더러 On
	ItemRenderer_->SetImage(HoldItemName_);

	// 렌더러 피벗위치 계산
	ItemRenderer_->GetTransform()->SetLocalScaling(_ItemSize);
	ItemRenderer_->On();
}

void MouseObject::ItemPutDown()
{
	// 아이템을 떨군다
	IsItemHold_ = false;
	HoldItemName_ = "";

	// 마우스 커서렌더러 On
	Mouse_->On();

	// 아이템렌더러 Off
	ItemRenderer_->Off();
}

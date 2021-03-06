#include "PreCompile.h"
#include "MouseObject.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "Portal.h"
#include "MonsterTopHPBar.h"

MouseObject::MouseObject() :
	PlayerUI_BottomStateBarCol_(false),
	PlayerUI_StatViewCol_(false),
	PlayerUI_SkillViewCol_(false),
	PlayerUI_IventoryViewCol_(false),
	PlayerUI_LWeaponSkillListBtnCol_(false),
	PlayerUI_RWeaponSkillListBtnCol_(false),
	PlayerUI_StoreViewCol_(false),
	NPCUI_TopMenuBarCol_(false),
	NPCUI_BuySellViewCol_(false),
	UI_PopupCol_(nullptr),
	MonsterCol_(false),
	CurMonsterCol_(nullptr),
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

	// 특수기능 커서
	GameEngineTexture* MouseBuy = GameEngineTextureManager::GetInst().Find("BuyCursor.png");
	MouseBuy->Cut(1, 1);
	GameEngineTexture* MouseSell = GameEngineTextureManager::GetInst().Find("SellCursor.png");
	MouseSell->Cut(1, 1);
	GameEngineTexture* MouseRepair = GameEngineTextureManager::GetInst().Find("RepairCursor.png");
	MouseRepair->Cut(1, 1);

	Mouse_ = CreateTransformComponent<GameEngineUIRenderer>();
	Mouse_->CreateAnimation("Mouse.png", "StayState", 0, 7, 0.4f);
	Mouse_->CreateAnimation("Mouse.png", "MoveState", 0, 0, 0.1f, false);

	// 특수기능에서의 커서 애니메이션
	Mouse_->CreateAnimation("BuyCursor.png", "BuyState", 0, 0, 0.1f, false);			// 구매버튼클릭시 활성화
	Mouse_->CreateAnimation("SellCursor.png", "SellState", 0, 0, 0.1f, false);			// 판매버튼클릭시 활성화
	Mouse_->CreateAnimation("RepairCursor.png", "RepairState", 0, 0, 0.1f, false);		// 수리버튼클릭시 활성화

	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));
	Mouse_->SetRenderGroup(static_cast<int>(UIRenderOrder::Mouse));
	Mouse_->SetChangeAnimation("StayState");

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
#pragma region 마우스충돌체크
	// UI관련
	MouseCollider_->Collision(CollisionType::CirCle, CollisionType::Rect, static_cast<int>(UIRenderOrder::UIMoveabledCheckCol), std::bind(&MouseObject::MouseUICollision, this, std::placeholders::_1), std::bind(&MouseObject::MouseUICollisionEnd, this, std::placeholders::_1));
	MouseCollider_->Collision(CollisionType::CirCle, CollisionType::Rect, static_cast<int>(UIRenderOrder::Popup_Action_Col), std::bind(&MouseObject::PopupUICollision, this, std::placeholders::_1), std::bind(&MouseObject::PopupUICollisionEnd, this, std::placeholders::_1));

	// Monster 관련
	MouseCollider_->Collision(CollisionType::CirCle, CollisionType::Rect, static_cast<int>(UIRenderOrder::Monster), std::bind(&MouseObject::MonsterCollision, this, std::placeholders::_1), std::bind(&MouseObject::MonsterCollisionEnd, this, std::placeholders::_1));
#pragma endregion

	float4 PrevPos = GameEngineInput::GetInst().GetPrevMouse3DPos();
	float4 CurPos = GameEngineInput::GetInst().GetMouse3DPos();

	// 마우스 위치 갱신
	GetTransform()->SetWorldPosition(float4(CurPos.x, CurPos.y));

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

	// 현재 레벨의 포탈이 존재하고 
	if (nullptr != GlobalValue::Portal)
	{
		if (true == GameEngineInput::GetInst().Down("MouseLButton"))
		{
			// 레벨이동이 활성화상태이고, 플레이어가 이동목표지점을 바꿧다면 해당 포탈의 활성화 해제
			if (true == GlobalValue::Portal->GetPortalInteractionFlag())
			{
				//GlobalValue::Portal->PortMoveableFlagOff();
			}
		}
	}

#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(MouseCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG
}

void MouseObject::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 타이틀 화면 or 로딩화면 or 캐릭터생성화면 or 캐릭터선택화면 or 엔딩화면 이동시 액터이동없음
	if (std::string::npos != _NextLevel->GetName().find("TitleLevel"))
	{
		// 전역마우스가 설정되어있다면 해제
		GlobalValue::CurMouse = nullptr;

		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("CreateCharacterLevel"))
	{
		// 전역마우스가 설정되어있다면 해제
		GlobalValue::CurMouse = nullptr;

		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("SelectCharacterLevel"))
	{
		// 전역마우스가 설정되어있다면 해제
		GlobalValue::CurMouse = nullptr;

		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("LoadingLevel"))
	{
		// 전역마우스가 설정되어있다면 해제
		GlobalValue::CurMouse = nullptr;

		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("MapEditorLevel"))
	{
		// 전역마우스가 설정되어있다면 해제
		GlobalValue::CurMouse = nullptr;

		return;
	}

	// 마우스 다음레벨 전달
	GetLevel()->SetLevelActorMove(_NextLevel, this);
}

void MouseObject::MouseUICollision(GameEngineCollision* _Other)
{
	// 마우스가 어떠한 UI와 충돌하든 충돌체크
	if (std::string::npos != _Other->GetName().find("Player_BottomStateBar"))
	{
		// 마우스가 플레이어 하단상태바와 충돌중
		PlayerUI_BottomStateBarCol_ = true;
	}
	else if (std::string::npos != _Other->GetName().find("Player_StatView"))
	{
		PlayerUI_StatViewCol_ = true;
	}
	else if (std::string::npos != _Other->GetName().find("Player_SkillView"))
	{
		PlayerUI_SkillViewCol_ = true;
	}
	else if (std::string::npos != _Other->GetName().find("Player_InventoryView"))
	{
		PlayerUI_IventoryViewCol_ = true;
	}
	else if (std::string::npos != _Other->GetName().find("Player_LWeaponSkill"))
	{
		PlayerUI_LWeaponSkillListBtnCol_ = true;
	}
	else if (std::string::npos != _Other->GetName().find("Player_RWeaponSkill"))
	{
		PlayerUI_RWeaponSkillListBtnCol_ = true;
	}
	else if (std::string::npos != _Other->GetName().find("Player_StoreView"))
	{
		PlayerUI_StoreViewCol_ = true;
	}
	else if (std::string::npos != _Other->GetName().find("NPC_TopMenu"))
	{
		NPCUI_TopMenuBarCol_ = true;
	}
	else if (std::string::npos != _Other->GetName().find("NPC_BuySellView"))
	{
		NPCUI_BuySellViewCol_ = true;
	}
}

void MouseObject::MouseUICollisionEnd(GameEngineCollision* _Other)
{
	if (std::string::npos != _Other->GetName().find("Player_BottomStateBar"))
	{
		// 마우스가 플레이어 하단상태바와 충돌종료
		PlayerUI_BottomStateBarCol_ = false;
	}
	else if (std::string::npos != _Other->GetName().find("Player_StatView"))
	{
		PlayerUI_StatViewCol_ = false;
	}
	else if (std::string::npos != _Other->GetName().find("Player_SkillView"))
	{
		PlayerUI_SkillViewCol_ = false;
	}
	else if (std::string::npos != _Other->GetName().find("Player_InventoryView"))
	{
		PlayerUI_IventoryViewCol_ = false;
	}
	else if (std::string::npos != _Other->GetName().find("Player_LWeaponSkill"))
	{
		PlayerUI_LWeaponSkillListBtnCol_ = false;
	}
	else if (std::string::npos != _Other->GetName().find("Player_RWeaponSkill"))
	{
		PlayerUI_RWeaponSkillListBtnCol_ = false;
	}
	else if (std::string::npos != _Other->GetName().find("Player_StoreView"))
	{
		PlayerUI_StoreViewCol_ = false;
	}
	else if (std::string::npos != _Other->GetName().find("NPC_TopMenu"))
	{
		NPCUI_TopMenuBarCol_ = false;
	}
	else if (std::string::npos != _Other->GetName().find("NPC_BuySellView"))
	{
		NPCUI_BuySellViewCol_ = false;
	}
}

void MouseObject::PopupUICollision(GameEngineCollision* _Other)
{
	// 팝업창과 충돌시작 & 충돌중시 호출
	UI_PopupCol_ = true;
}

void MouseObject::PopupUICollisionEnd(GameEngineCollision* _Other)
{
	// 팝업창과 충돌종료시 호출
	UI_PopupCol_ = false;
}

void MouseObject::MonsterCollision(GameEngineCollision* _Other)
{
	if (false == MonsterCol_)
	{
		// 몬스터와 충돌시작 & 충돌중시 호출
		MonsterCol_ = true;

		// 충돌중인 몬스터 저장
		CurMonsterCol_ = _Other;
	}
}

void MouseObject::MonsterCollisionEnd(GameEngineCollision* _Other)
{
	if (true == MonsterCol_)
	{
		// 몬스터와 충돌종료시 호출
		MonsterCol_ = false;

		// 충돌중인 몬스터 초기화
		CurMonsterCol_ = nullptr;
		
		// 상단 HP Bar Off
		GlobalValue::TopHPBar->CurMonsterTopHPBarOff();
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

void MouseObject::BuyCursorActive()
{
	// 커서 애니메이션 변경
	Mouse_->SetChangeAnimation("BuyState");
	Mouse_->GetTransform()->SetLocalScaling(float4(32.f, 40.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(14.5f, -22.5f));

	// 현재 마우스상태 변경
	State_ = MouseState::Buy;
}

void MouseObject::BuyCursorInActive()
{
	// 커서 애니메이션 변경
	Mouse_->SetChangeAnimation("StayState");
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));

	// 현재 마우스상태 변경
	State_ = MouseState::Stay;
}

void MouseObject::SellCursorActive()
{
	// 커서 애니메이션 변경
	Mouse_->SetChangeAnimation("SellState");
	Mouse_->GetTransform()->SetLocalScaling(float4(32.f, 40.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(14.5f, -22.5f));

	// 현재 마우스상태 변경
	State_ = MouseState::Sell;
}

void MouseObject::SellCursorInactive()
{
	// 커서 애니메이션 변경
	Mouse_->SetChangeAnimation("StayState");
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));

	// 현재 마우스상태 변경
	State_ = MouseState::Stay;
}

void MouseObject::RepairCursorActive()
{
	// 커서 애니메이션 변경
	Mouse_->SetChangeAnimation("RepairState");
	Mouse_->GetTransform()->SetLocalScaling(float4(32.f, 40.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(14.5f, -22.5f));

	// 현재 마우스상태 변경
	State_ = MouseState::Repair;
}

void MouseObject::RepairCursorInactive()
{
	// 커서 애니메이션 변경
	Mouse_->SetChangeAnimation("StayState");
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));

	// 현재 마우스상태 변경
	State_ = MouseState::Stay;
}

void MouseObject::CursorStateReset()
{
	// 커서 애니메이션 변경
	Mouse_->SetChangeAnimation("StayState");
	Mouse_->GetTransform()->SetLocalScaling(float4(33.f, 29.f, 1.f));
	Mouse_->GetTransform()->SetLocalPosition(float4(15.5f, -11.5f));

	// 현재 마우스상태 변경
	State_ = MouseState::Stay;
}

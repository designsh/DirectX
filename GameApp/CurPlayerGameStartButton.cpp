#include "PreCompile.h"
#include "CurPlayerGameStartButton.h"

#include "ErrorMsgPopup.h"
#include "ClassSelectObject.h"
#include "CreateCharacterInputText.h"
#include "MainPlayerInfomation.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "UserGame.h"
#include "GlobalValue.h"

bool CurPlayerGameStartButton::ClassSelect_ = false;

void CurPlayerGameStartButton::UserClassSelect()
{
	ClassSelect_ = true;
}

void CurPlayerGameStartButton::UserClassDeselect()
{
	ClassSelect_ = false;
}

CurPlayerGameStartButton::CurPlayerGameStartButton() :
	ButtonState_(Button_State::Normal),
	CurPlayerGameStartBtn_(nullptr),
	MainCollider_(nullptr),
	RenderFlag_(false),
	ButtonClickSound_(nullptr)
{
}

CurPlayerGameStartButton::~CurPlayerGameStartButton()
{
}

void CurPlayerGameStartButton::Start()
{
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("ShortButton_Stay.png");
	ButtonDefault->Cut(1, 1);

	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("ShortButton_Click.png");
	ButtonClick->Cut(1, 1);

	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	CurPlayerGameStartBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	CurPlayerGameStartBtn_->CreateAnimation("ShortButton_Stay.png", "Default", 0, 0, 0.1f, false);
	CurPlayerGameStartBtn_->CreateAnimation("ShortButton_Click.png", "Click", 0, 0, 0.1f, false);
	CurPlayerGameStartBtn_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.f));
	CurPlayerGameStartBtn_->GetTransform()->SetLocalPosition(float4(WindowSize.ihx() - 80.f, -WindowSize.ihy() + 60.f));
	CurPlayerGameStartBtn_->Off();
	CurPlayerGameStartBtn_->SetChangeAnimation("Default");

	// OK TextSetting
	CurPlayerGameStartBtn_->TextSetting("diablo", "OK", 15, FW1_VCENTER | FW1_CENTER, float4::BLACK);

	MainCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollider_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	MainCollider_->GetTransform()->SetLocalPosition(CurPlayerGameStartBtn_->GetTransform()->GetLocalPosition());
	MainCollider_->Off();

	// 사운드플레이어 생성
	ButtonClickSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void CurPlayerGameStartButton::Update(float _DeltaTime)
{
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 게임시작 조건 검사 후 조건일치시 게임 생성
			GameStartConditionCheck();
			ButtonState_ = Button_State::Normal;
		}
	}

	DebugRender();

	// 충돌체크
	if (true == CurPlayerGameStartBtn_->IsUpdate())
	{
		MainCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&CurPlayerGameStartButton::OKButtonClick, this, std::placeholders::_1));
	}

	// 1. 버튼 활성/비활성 여부 판단
	if (false == RenderFlag_)
	{
		if (true == ClassSelect_)
		{
			CurPlayerGameStartBtn_->On();
			MainCollider_->On();
			RenderFlag_ = true;
		}
	}
	else
	{
		if (false == ClassSelect_)
		{
			CurPlayerGameStartBtn_->Off();
			MainCollider_->Off();
			RenderFlag_ = false;
		}
	}
}

void CurPlayerGameStartButton::ChangeStartReset()
{
	CurPlayerGameStartBtn_->SetChangeAnimation("Default");
}

void CurPlayerGameStartButton::DebugRender()
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(MainCollider_->GetTransform(), CollisionType::Rect);
#endif
}

void CurPlayerGameStartButton::OKButtonClick(GameEngineCollision* _OtherCollision)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		CurPlayerGameStartBtn_->SetChangeAnimation("Click");
		ButtonState_ = Button_State::Click;

		// 효과음 재생
		ButtonClickSound_->PlayAlone("button.wav", 0);
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		CurPlayerGameStartBtn_->SetChangeAnimation("Default");
	}
}

void CurPlayerGameStartButton::GameStartConditionCheck()
{
	// 현재 선택된 직업(클래스)가 있는지 검사
	// 직업을 선택해야만 확인버튼 활성화
	if (JobType::None != ClassSelectObject::GetSelectClass())
	{
		// 선택된 직업(클래스)가 있다면 생성 가능한 플레이어 ID인지 검사 후
		// 정상적이라면 플레이어 정보 생성 및 정보파일 저장
		// 비정상이라면 경고창이 화면에 표시되며, 정보 생성 및 레벨전환 불가
		CheckSameID();
	}
}

void CurPlayerGameStartButton::CheckSameID()
{
	// 버튼클릭 시점에 호출되며, 지정된 경로에 해당 ID와 같은이름이 존재한다면
	// 경고창을 화면에 표시하며, 존재하지않다면 해당 ID로 파일을 생성

	// 1. 버튼클릭 시점에 CreateCharacterInputText에 입력된 Text Get
	std::string CurID = CreateCharacterInputText::GetInputID();
	if (true == CurID.empty()) // 입력한 ID가 없다면 경고창 표시
	{
		// ID를 입력하시오!!!! 경고창 표시
		ErrorMsgPopup* ErrorMsg = GetLevel()->CreateActor<ErrorMsgPopup>();
		ErrorMsg->ErrorMsgPopupActive("Input character ID!!!");

		return;
	}

	// 2. 해당 ID를 파일명으로 가지는 파일이 존재하는지 탐색
	if (false == DefaultPathFileNameCheck(CurID))
	{
		// 같은 ID의 플레이어가 이미 존재합니다!!!! 경고창 표시
		ErrorMsgPopup* ErrorMsg = GetLevel()->CreateActor<ErrorMsgPopup>();
		ErrorMsg->ErrorMsgPopupActive("This ID already exists!!!");

		return;
	}

	// 3. 동일한 ID가 없다면 플레이어 정보 생성
	CreateCurPlayer(CurID);
}

bool CurPlayerGameStartButton::DefaultPathFileNameCheck(const std::string& _PlayerID)
{
	// 생성된 플레이어 파일 경로에 해당 ID의 파일이 존재하면 동일 이름 플레이어가 존재하므로 경고창 표시
	GameEngineDirectory PlayerFileDir;
	PlayerFileDir.MoveParent("DirectX");
	PlayerFileDir.MoveChild("Resources");
	PlayerFileDir.MoveChild("SaveFile");
	if (true == PlayerFileDir.CheckSameFileName(_PlayerID, ".dat"))
	{
		return false;
	}
	
	return true;
}

void CurPlayerGameStartButton::CreateCurPlayer(const std::string& _PlayerID)
{
	JobType CurClass = ClassSelectObject::GetSelectClass();
	if (JobType::None != CurClass)
	{
		// 메인플레이어 정보 생성 및 해당 플레이어 파일 생성
		MainPlayerInfomation::GetInst().CreateMainPlayerInfo(_PlayerID, CurClass);

		// 생성완료 후 레벨 전환
		UserGame::LevelChange("LoadingLevel");
	}
}

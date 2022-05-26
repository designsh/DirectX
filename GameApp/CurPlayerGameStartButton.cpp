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

	// �����÷��̾� ����
	ButtonClickSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void CurPlayerGameStartButton::Update(float _DeltaTime)
{
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ���ӽ��� ���� �˻� �� ������ġ�� ���� ����
			GameStartConditionCheck();
			ButtonState_ = Button_State::Normal;
		}
	}

	DebugRender();

	// �浹üũ
	if (true == CurPlayerGameStartBtn_->IsUpdate())
	{
		MainCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&CurPlayerGameStartButton::OKButtonClick, this, std::placeholders::_1));
	}

	// 1. ��ư Ȱ��/��Ȱ�� ���� �Ǵ�
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

		// ȿ���� ���
		ButtonClickSound_->PlayAlone("button.wav", 0);
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		CurPlayerGameStartBtn_->SetChangeAnimation("Default");
	}
}

void CurPlayerGameStartButton::GameStartConditionCheck()
{
	// ���� ���õ� ����(Ŭ����)�� �ִ��� �˻�
	// ������ �����ؾ߸� Ȯ�ι�ư Ȱ��ȭ
	if (JobType::None != ClassSelectObject::GetSelectClass())
	{
		// ���õ� ����(Ŭ����)�� �ִٸ� ���� ������ �÷��̾� ID���� �˻� ��
		// �������̶�� �÷��̾� ���� ���� �� �������� ����
		// �������̶�� ���â�� ȭ�鿡 ǥ�õǸ�, ���� ���� �� ������ȯ �Ұ�
		CheckSameID();
	}
}

void CurPlayerGameStartButton::CheckSameID()
{
	// ��ưŬ�� ������ ȣ��Ǹ�, ������ ��ο� �ش� ID�� �����̸��� �����Ѵٸ�
	// ���â�� ȭ�鿡 ǥ���ϸ�, ���������ʴٸ� �ش� ID�� ������ ����

	// 1. ��ưŬ�� ������ CreateCharacterInputText�� �Էµ� Text Get
	std::string CurID = CreateCharacterInputText::GetInputID();
	if (true == CurID.empty()) // �Է��� ID�� ���ٸ� ���â ǥ��
	{
		// ID�� �Է��Ͻÿ�!!!! ���â ǥ��
		ErrorMsgPopup* ErrorMsg = GetLevel()->CreateActor<ErrorMsgPopup>();
		ErrorMsg->ErrorMsgPopupActive("Input character ID!!!");

		return;
	}

	// 2. �ش� ID�� ���ϸ����� ������ ������ �����ϴ��� Ž��
	if (false == DefaultPathFileNameCheck(CurID))
	{
		// ���� ID�� �÷��̾ �̹� �����մϴ�!!!! ���â ǥ��
		ErrorMsgPopup* ErrorMsg = GetLevel()->CreateActor<ErrorMsgPopup>();
		ErrorMsg->ErrorMsgPopupActive("This ID already exists!!!");

		return;
	}

	// 3. ������ ID�� ���ٸ� �÷��̾� ���� ����
	CreateCurPlayer(CurID);
}

bool CurPlayerGameStartButton::DefaultPathFileNameCheck(const std::string& _PlayerID)
{
	// ������ �÷��̾� ���� ��ο� �ش� ID�� ������ �����ϸ� ���� �̸� �÷��̾ �����ϹǷ� ���â ǥ��
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
		// �����÷��̾� ���� ���� �� �ش� �÷��̾� ���� ����
		MainPlayerInfomation::GetInst().CreateMainPlayerInfo(_PlayerID, CurClass);

		// �����Ϸ� �� ���� ��ȯ
		UserGame::LevelChange("LoadingLevel");
	}
}

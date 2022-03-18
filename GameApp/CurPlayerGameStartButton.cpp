#include "PreCompile.h"
#include "CurPlayerGameStartButton.h"

#include "ErrorMsgPopup.h"
#include "ClassSelectObject.h"
#include "CreateCharacterInputText.h"
#include "MainPlayerInfomation.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "UserGame.h"
#include "GlobalEnumClass.h"
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
	CurPlayerGameStartBtn_(nullptr),
	MainCollider_(nullptr),
	RenderFlag_(false)
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
	CurPlayerGameStartBtn_->GetTransform()->SetLocalScaling(float4(150.f, 40.f, 1.f));
	CurPlayerGameStartBtn_->GetTransform()->SetLocalPosition(float4(WindowSize.ihx() - 130.f, -WindowSize.ihy() + 60.f));
	CurPlayerGameStartBtn_->Off();
	CurPlayerGameStartBtn_->SetChangeAnimation("Default");

	MainCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollider_->GetTransform()->SetLocalScaling(float4(150.f, 40.f, 1.0f));
	MainCollider_->GetTransform()->SetLocalPosition(CurPlayerGameStartBtn_->GetTransform()->GetLocalPosition());
	MainCollider_->Off();
}

void CurPlayerGameStartButton::Update(float _DeltaTime)
{
	DebugRender();

	// �浹üũ
	if (true == CurPlayerGameStartBtn_->IsUpdate())
	{
		MainCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&CurPlayerGameStartButton::OKButtonClick, this, std::placeholders::_1));
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
	GetLevel()->PushDebugRender(MainCollider_->GetTransform(), CollisionType::Rect);
}

void CurPlayerGameStartButton::OKButtonClick(GameEngineCollision* _OtherCollision)
{
	// ���콺�� �浹��
	if (true == GameEngineInput::GetInst().Free("MouseLButton"))
	{
		CurPlayerGameStartBtn_->SetChangeAnimation("Default");
	}

	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		CurPlayerGameStartBtn_->SetChangeAnimation("Click");

		GameStartConditionCheck();
	}
}

void CurPlayerGameStartButton::GameStartConditionCheck()
{
	// ���� ���õ� ����(Ŭ����)�� �ִ��� �˻�
	if (JobType::None != ClassSelectObject::GetSelectClass())
	{
		// ���õ� ����(Ŭ����)�� �ִٸ� ���� ������ �÷��̾� ID���� �˻� ��
		// �������̶�� �÷��̾� ���� ���� �� �������� ����
		// �������̶�� ���â�� ȭ�鿡 ǥ�õǸ�, ���� ���� �� ������ȯ �Ұ�
		CheckSameID();
	}
	else
	{
		// ���� ���õ� ������ ������ ����� ǥ��
		// �÷����Ϸ��� Ŭ������ �����Ͻʽÿ�!!!!!
		ErrorMsgPopup* ErrorMsg = GetLevel()->CreateActor<ErrorMsgPopup>();
		ErrorMsg->ErrorMsgPopupActive("Please select a Class(Job)!!!!");
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
		ErrorMsg->ErrorMsgPopupActive("Please enter your character ID!!!!");

		return;
	}

	// 2. �ش� ID�� ���ϸ����� ������ ������ �����ϴ��� Ž��
	if (true == DefaultPathFileNameCheck(CurID))
	{
		// ���� ID�� �÷��̾ �̹� �����մϴ�!!!! ���â ǥ��
		ErrorMsgPopup* ErrorMsg = GetLevel()->CreateActor<ErrorMsgPopup>();
		ErrorMsg->ErrorMsgPopupActive("This ID already exists.Please enter a new ID");

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
		// ������ ���ϸ��� ã��
		return true;
	}
	
	return false;
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

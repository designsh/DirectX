#include "PreCompile.h"
#include "TakeInOutGoldPopup.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

TakeInOutGoldPopup::TakeInOutGoldPopup() :
	PopupType_(TakeInOutPopupType::NONE),
	CreateType_(TakeInOutPopCreateType::NONE),
	MaxHaveGole_(0),
	CurHaveGold_(0),
	Panel_(nullptr),
	GoldText_(nullptr),
	GoldUpBtn_(nullptr),
	GoldUpBtnCol_(nullptr),
	GoldUpBtn_State_(Button_State::Normal),
	GoldDownBtn_(nullptr),
	GoldDownBtnCol_(nullptr),
	GoldDownBtn_State_(Button_State::Normal),
	CloseBtn_(nullptr),
	CloseBtnCol_(nullptr),
	CloseBtn_State_(Button_State::Normal),
	ApprovedBtn_(nullptr),
	ApprovedCol_(nullptr),
	ApprovedBtn_State_(Button_State::Normal)
{


}

TakeInOutGoldPopup::~TakeInOutGoldPopup()
{
}

void TakeInOutGoldPopup::Start()
{
	// ImageCutting

	// �����ư
	GameEngineTexture* CloseButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	CloseButtonDefault->Cut(1, 1);
	GameEngineTexture* CloseButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	CloseButtonClick->Cut(1, 1);

	// ���ι�ư
	GameEngineTexture* ApprovedButtonDefault = GameEngineTextureManager::GetInst().Find("ApprovedButton_Default.png");
	ApprovedButtonDefault->Cut(1, 1);
	GameEngineTexture* ApprovedButtonClick = GameEngineTextureManager::GetInst().Find("ApprovedButton_Click.png");
	ApprovedButtonClick->Cut(1, 1);

	Off();
}

void TakeInOutGoldPopup::Update(float _DeltaTime)
{
#pragma region ��ư����üũ
	if (GoldUpBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��差 ����(������/�ֱ�)
			GoldUp();

			GoldUpBtn_State_ = Button_State::Normal;
		}
	}

	if (GoldDownBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��差 ����(������/�ֱ�)
			GoldDown();

			GoldDownBtn_State_ = Button_State::Normal;
		}
	}

	if (CloseBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// �ش� â ��Ȱ��
			Close();

			CloseBtn_State_ = Button_State::Normal;
		}
	}

	if (ApprovedBtn_State_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ����
			Approved();

			ApprovedBtn_State_ = Button_State::Normal;
		}
	}
#pragma endregion

#pragma region �� ��ư �浹ü������ �� �浹üũ
	if (nullptr != GoldUpBtnCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(GoldUpBtnCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		GoldUpBtnCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&TakeInOutGoldPopup::GoldUpButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != GoldDownBtnCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(GoldDownBtnCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		GoldDownBtnCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&TakeInOutGoldPopup::GoldDownButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != CloseBtnCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(CloseBtnCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		CloseBtnCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&TakeInOutGoldPopup::CloseButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != ApprovedCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(ApprovedCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		ApprovedCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&TakeInOutGoldPopup::ApprovedButtonClick, this, std::placeholders::_1));
	}
#pragma endregion
}

void TakeInOutGoldPopup::GoldUpButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		GoldUpBtn_->SetChangeAnimation("Click");

		GoldUpBtn_State_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		GoldUpBtn_->SetChangeAnimation("Default");
	}
}

void TakeInOutGoldPopup::GoldDownButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		GoldDownBtn_->SetChangeAnimation("Click");

		GoldDownBtn_State_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		GoldDownBtn_->SetChangeAnimation("Default");
	}
}

void TakeInOutGoldPopup::CloseButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		CloseBtn_->SetChangeAnimation("Click");

		CloseBtn_State_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		CloseBtn_->SetChangeAnimation("Default");
	}
}

void TakeInOutGoldPopup::ApprovedButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		ApprovedBtn_->SetChangeAnimation("Click");

		ApprovedBtn_State_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		ApprovedBtn_->SetChangeAnimation("Default");
	}
}

void TakeInOutGoldPopup::GoldUp()
{
	// ���� ȭ�鿡 ǥ�õǴ� ��带 1�� ����
	// ��, ������差�� �ִ�ġ�� �Ѿ�� ����ؼ� ������差�� �ִ�ġ�� ����

}

void TakeInOutGoldPopup::GoldDown()
{
	// ���� ȭ�鿡 ǥ�õǴ� ��带 1 ����
	// ��, 0���Ϸ� �������� ����ؼ� 0���� ����

}

void TakeInOutGoldPopup::Close()
{
	// �ش� â�� �ݴ´�.

}

void TakeInOutGoldPopup::Approved()
{
	// �ش� â�� Ÿ�԰� �ش�â�� ������ ������ Ÿ�Կ� ���� 
	// �ش�â�� ������ ���Ϳ��� �ش� ��差�� ���ϰų� ���ش�.


}

void TakeInOutGoldPopup::CreateTakePopup(TakeInOutPopupType _PopupType, TakeInOutPopCreateType _CreateType, const float4& _InitPos)
{
	// ��������
	PopupType_ = _PopupType;
	CreateType_ = _CreateType;

	// �ǳ� ����
	Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup));
	Panel_->SetImage("TakeInOutGoldView_Panel.png");
	Panel_->GetTransform()->SetLocalPosition(_InitPos);

	// ���� �ؽ�Ʈ ǥ�ø� ���� UI������ ����
	if (TakeInOutPopupType::TakeIn == PopupType_)
	{
		// �ֱ�� �˾����� ������
		//GoldText_ = createt

	}
	else
	{
		// ������� �˾����� ������


	}


	// �������� ��ư����

	// ���ڰ��� ��ư����

	// ���� ��ư����

	// ���� ��ư����

}

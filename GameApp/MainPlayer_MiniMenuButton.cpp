#include "PreCompile.h"
#include "MainPlayer_MiniMenuButton.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"

#include "StatView.h"

#include "MainPlayer_MiniMenu.h"

MainPlayer_MiniMenuButton::MainPlayer_MiniMenuButton() :
	Parent_(nullptr),
	Active_(false),
	ButtonState_(Button_State::Normal),
	ShortcutsType_(ShortcutsType::NONE),
	DefaultButtonName_{},
	ClickButtonName_{},
	BasicButtonPos_(float4::ZERO),
	MoveButtonPos_(float4(100.f, 0.f, 0.f)),
	ButtonRenderer_(nullptr),
	ButtonCollision_(nullptr)
{
}

MainPlayer_MiniMenuButton::~MainPlayer_MiniMenuButton()
{
}

void MainPlayer_MiniMenuButton::Start()
{
}

void MainPlayer_MiniMenuButton::Update(float _DeltaTime)
{
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// �ٷΰ��� ��ư�� ���� ó��
			ShortcutsProcess();

			ButtonRenderer_->SetChangeAnimation("Default");

			ButtonState_ = Button_State::Normal;
		}
	}

	if (nullptr != ButtonCollision_)
	{
		ButtonCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_MiniMenuButton::ShortcutsButtonClick, this, std::placeholders::_1));
	}
}

void MainPlayer_MiniMenuButton::ShortcutsButtonClick(GameEngineCollision* _Other)
{
	if (nullptr != ButtonRenderer_)
	{
		// Mouse LButton Flag Check
		if (true == GameEngineInput::GetInst().Down("MouseLButton"))
		{
			ButtonRenderer_->SetChangeAnimation("Click");

			ButtonState_ = Button_State::Click;
		}
		else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			ButtonRenderer_->SetChangeAnimation("Default");
		}
	}
}

void MainPlayer_MiniMenuButton::ShortcutsProcess()
{
	// Ȱ��ȭ Flag On
	if (false == Active_)
	{
		Active_ = true;
	}
	else
	{
		Active_ = false;
	}

	// �ٷΰ��� �޴��� ���� ó��
	switch (ShortcutsType_)
	{
		case ShortcutsType::STATVIEW:
		{
			// ����â Ȱ��ȭ
			GlobalValue::CurPlayer->StateViewEnabled(Active_);
			break;
		}
		case ShortcutsType::INVENTORY:
		{
			// �κ��丮 Ȱ��ȭ
			//GlobalValue::CurPlayer->InventoryViewEnabled(Active_);
			break;
		}
		case ShortcutsType::SKILLVIEW:
		{
			// ��ųâ Ȱ��ȭ
			//GlobalValue::CurPlayer->SkillViewEnabled(Active_);
			break;
		}
	}

	// �̴ϸ޴� �̵�ó��
	MoveButtonPosition();
}

void MainPlayer_MiniMenuButton::CreateShortcutsButton(MainPlayer_MiniMenu* _Parent, const std::string& _Name, const float4& _Pos, ShortcutsType _Type)
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	Parent_ = _Parent;
	DefaultButtonName_ = _Name;
	ClickButtonName_ = _Name;
	BasicButtonPos_ = _Pos;
	ShortcutsType_ = _Type;

	// �̸� ����
	DefaultButtonName_ += "_Default.png";
	ClickButtonName_ += "_Click.png";

	// �̹��� ����
	GameEngineTexture* Click = GameEngineTextureManager::GetInst().Find(ClickButtonName_);
	Click->Cut(1, 1);
	GameEngineTexture* Default = GameEngineTextureManager::GetInst().Find(DefaultButtonName_);
	Default->Cut(1, 1);

	// ������ ����
	ButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI12));
	ButtonRenderer_->CreateAnimation(ClickButtonName_, "Click", 0, 0, 0.1f, false);
	ButtonRenderer_->CreateAnimation(DefaultButtonName_, "Default", 0, 0, 0.1f, false);
	ButtonRenderer_->GetTransform()->SetLocalScaling(float4(20.f, 20.f, 1.0f));
	ButtonRenderer_->GetTransform()->SetLocalPosition(BasicButtonPos_);
	ButtonRenderer_->SetChangeAnimation("Default");

	// �浹ü ����
	ButtonCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI12_Collider));
	ButtonCollision_->GetTransform()->SetLocalScaling(ButtonRenderer_->GetTransform()->GetLocalScaling());
	ButtonCollision_->GetTransform()->SetLocalPosition(ButtonRenderer_->GetTransform()->GetLocalPosition());
}

void MainPlayer_MiniMenuButton::MoveButtonPosition()
{
	// Ȱ��ȭ�� â������ �̵���ġ ����

	// ����â�� Ȱ��ȭ ���¶��
	if (true == GlobalValue::CurPlayer->GetStatView()->IsUpdate())
	{
		// ��ųâ or �κ��丮â�� ���� Ȱ��ȭ �Ǿ��ִٸ�
		// �̴ϸ޴���� Off


		// �ƴ϶�� ȭ���� ���������� �̵�
		Parent_->AllMoveMiniMenu(MoveButtonPos_);
	}
	else
	{
		// ��ųâ or �κ��丮â�� Ȱ��ȭ���¶��
		// �̴ϸ޴���� �������� �̵�
		//float4 LeftMovePos = MoveButtonPos_;



		// �ƴ϶�� ������ ��ġ�� �̵�
		float4 BasicMovePos = MoveButtonPos_;
		BasicMovePos.x *= -1;

		Parent_->AllMoveMiniMenu(BasicMovePos);
	}

	//// ��ųâ�� Ȱ��ȭ ���¶��
	//if (true == GlobalValue::CurPlayer->GetSkillView()->IsUpdate())
	//{

	//}
	//else
	//{

	//}

	//// �κ��丮â�� Ȱ��ȭ ���¶��
	//if (true == GlobalValue::CurPlayer->GetInventoryView()->IsUpdate())
	//{

	//}
	//else
	//{

	//}

}
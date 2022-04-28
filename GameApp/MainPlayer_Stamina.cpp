#include "PreCompile.h"
#include "MainPlayer_Stamina.h"

#include <GameEngine/GameEngineProgressBarRenderer.h>
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

#include "GlobalValue.h"

MainPlayer_Stamina::MainPlayer_Stamina() :
	StaminaProgressBarRenderer_(nullptr),
	StaminaButton_(nullptr),
	StaminaButtonCollision_(nullptr),
	RunActive_(false),
	ButtonState_(Button_State::Normal),
	Stamina30Percent_(false),
	MaxStamina_(1.0f),
	CurStamina_(1.0f),
	StaminaDrain_(30.f)
{
}

MainPlayer_Stamina::~MainPlayer_Stamina()
{
}

void MainPlayer_Stamina::Start()
{
	// StaminaButton Image Cutting
	GameEngineTexture* EnableDefault = GameEngineTextureManager::GetInst().Find("Run_Default.png");
	EnableDefault->Cut(1, 1);
	GameEngineTexture* EnableClick = GameEngineTextureManager::GetInst().Find("Run_Click.png");
	EnableClick->Cut(1, 1);

	GameEngineTexture* DisabledDefault = GameEngineTextureManager::GetInst().Find("Walk_Default.png");
	DisabledDefault->Cut(1, 1);
	GameEngineTexture* DisabledClick = GameEngineTextureManager::GetInst().Find("Walk_Click.png");
	DisabledClick->Cut(1, 1);

	// Screen Harf Size Get
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// ���¹̳� ProgressBar
	StaminaProgressBarRenderer_ = CreateTransformComponent<GameEngineProgressBarRenderer>(static_cast<int>(UIRenderOrder::UI11));
	StaminaProgressBarRenderer_->SetImage("StaminaBar.png");
	StaminaProgressBarRenderer_->SetProgressBarDirect(static_cast<int>(ProgressBarDirect::RightToLeft));
	StaminaProgressBarRenderer_->GetTransform()->SetLocalPosition(float4(-77.f, 18.f - ScreenHarfSize.y));

	// ���¹̳� Ȱ��/��Ȱ�� ��ư
	StaminaButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));
	StaminaButton_->CreateAnimation("Run_Default.png", "RunDefault", 0, 0, 0.1f, false);
	StaminaButton_->CreateAnimation("Run_Click.png", "RunClick", 0, 0, 0.1f, false);
	StaminaButton_->CreateAnimation("Walk_Default.png", "WalkDefault", 0, 0, 0.1f, false);
	StaminaButton_->CreateAnimation("Walk_Click.png", "WalkClick", 0, 0, 0.1f, false);
	StaminaButton_->GetTransform()->SetLocalScaling(float4(16.f, 20.f, 1.0f));
	StaminaButton_->GetTransform()->SetLocalPosition(float4(-138.f, 19.f - ScreenHarfSize.y));
	StaminaButton_->SetChangeAnimation("WalkDefault");

	// ���¹̳� Ȱ��/��Ȱ�� ��ư �浹ü
	StaminaButtonCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI11_Collider));
	StaminaButtonCollision_->GetTransform()->SetLocalScaling(float4(16.f, 20.f, 1.0f));
	StaminaButtonCollision_->GetTransform()->SetLocalPosition(StaminaButton_->GetTransform()->GetLocalPosition());
}

void MainPlayer_Stamina::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(StaminaButtonCollision_->GetTransform(), CollisionType::Rect);
#endif // DEBUG

	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ��ư ���� ��ȯ
			StaminaEnableOrDisabled();

			ButtonState_ = Button_State::Normal;
		}
	}

	// ���¹̳� �Ҹ� ���
	CalculationStaminaConsumption(_DeltaTime);

	// ���¹̳� Ȱ��ȭ��ư �浹üũ
	StaminaButtonCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_Stamina::StaminaActiveButtonClick, this, std::placeholders::_1));
}

void MainPlayer_Stamina::InitStaminaDrain()
{
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();
	StaminaDrain_ = static_cast<float>(PlayerInfo.RunStaminaDrain);
}

void MainPlayer_Stamina::CalculationStaminaConsumption(float _DeltaTime)
{
	// �����÷��̾ �����Ҷ�
	if (nullptr != GlobalValue::CurPlayer)
	{
		// �����÷��̾ �ٱ�����̸� ���¹̳� �Ҹ� ���
		if (true == GlobalValue::CurPlayer->GetIsRun())
		{
			// �÷��̾ ���� �ʵ��϶� �Ҹ�
			if (false == GlobalValue::CurPlayer->GetIsTown())
			{
				// �̵����϶� �Ҹ�
				if (true == GlobalValue::CurPlayer->GetIsMove())
				{
					// �ð��� ���� ���¹̳� �Ҹ�
					if (0.f <= CurStamina_)
					{
						CurStamina_ -= (StaminaDrain_ * 0.01f) * _DeltaTime;
						StaminaProgressBarRenderer_->SetPercent(CurStamina_);

						// ���¹̳����� 30%�����̸� ���¹̳� ������ȯ�Ѵ�.
						if (0.3f >= CurStamina_ && false == Stamina30Percent_)
						{
							StaminaProgressBarRenderer_->SetResultColor(float4::RED);

							Stamina30Percent_ = true;
						}
					}

					// ���¹̳����� 0%�����̸� �÷��̾�� �ȱ���·� ��ȯ�ȴ�.
					if (0.f >= CurStamina_)
					{
						if (true == GlobalValue::CurPlayer->GetIsTown())
						{
							GlobalValue::CurPlayer->ChangeFSMState("Walk_Town");
						}
						else
						{
							GlobalValue::CurPlayer->ChangeFSMState("Walk_Field");
						}
					}
				}
				else // �̵����� �ƴҶ�
				{
					// ���¹̳����� 100%�� �ƴ϶�� ȸ��
					if (1.f >= CurStamina_)
					{
						// ���¹̳����� 30% �̻��̵Ǹ� ����(1,1,1,1)�� ��ȯ �� ����ȯ Flag ����
						CurStamina_ += (StaminaDrain_ * 0.01f) * _DeltaTime;
						StaminaProgressBarRenderer_->SetPercent(CurStamina_);

						if (0.3f <= CurStamina_ && true == Stamina30Percent_)
						{
							StaminaProgressBarRenderer_->SetResultColor(float4::ONE);

							Stamina30Percent_ = false;
						}
					}
				}
			}
		}
		else // �����÷��̾ �ȱ�����϶�
		{
			// ���¹̳����� 100%�� �ƴ϶�� ȸ��
			if (1.f >= CurStamina_)
			{
				// ���¹̳����� 30% �̻��̵Ǹ� ����(1,1,1,1)�� ��ȯ �� ����ȯ Flag ����
				CurStamina_ += (StaminaDrain_ * 0.01f) * _DeltaTime;
				StaminaProgressBarRenderer_->SetPercent(CurStamina_);

				if (0.3f <= CurStamina_ && true == Stamina30Percent_)
				{
					StaminaProgressBarRenderer_->SetResultColor(float4::ONE);

					Stamina30Percent_ = false;
				}
			}
		}
	}
}

void MainPlayer_Stamina::StaminaEnableOrDisabled()
{
	if (nullptr != GlobalValue::CurPlayer)
	{
		// �÷��̾� �ȱ�/�ٱ� Flag ��ȯ
		GlobalValue::CurPlayer->SetIsRun(RunActive_);

		// �÷��̾ �̵����̶�� ���¹ٷ���ȯ
		if (true == GlobalValue::CurPlayer->GetIsMove())
		{
			if (false == RunActive_)
			{
				if (true == GlobalValue::CurPlayer->GetIsTown())
				{
					GlobalValue::CurPlayer->ChangeFSMState("Walk_Town");
				}
				else
				{
					GlobalValue::CurPlayer->ChangeFSMState("Walk_Field");
				}
			}
			else
			{
				GlobalValue::CurPlayer->ChangeFSMState("Run");
			}
		}
	}
}

void MainPlayer_Stamina::StaminaActiveButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// ���� ���� üũ�� ���� ��ư �ؽ��� ��ȯ
		if (false == RunActive_) // �ȱ� -> �ٱ�
		{
			StaminaButton_->SetChangeAnimation("WalkClick");

			RunActive_ = true;
		}
		else // �ٱ� -> �ȱ�
		{
			StaminaButton_->SetChangeAnimation("RunClick");

			RunActive_ = false;
		}

		ButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		// ���� ���� üũ�� ���� ��ư �ؽ��� ��ȯ
		if (false == RunActive_) // ���� �ȱ� ����
		{
			StaminaButton_->SetChangeAnimation("WalkDefault");
		}
		else // ���� �ٱ����
		{
			StaminaButton_->SetChangeAnimation("RunDefault");
		}
	}
}

void MainPlayer_Stamina::SetStaminaActive(bool _Flag)
{
	// Flag ����
	RunActive_ = _Flag;

	// Flag�� ���� ������ȯ
	if (false == RunActive_) // �ȱ���¶��
	{
		StaminaButton_->SetChangeAnimation("WalkDefault");
	}
	else // �ٱ���¶��
	{
		StaminaButton_->SetChangeAnimation("RunDefault");
	}

	// �÷��̾ �̵����̶�� �ٷ� ������ȯ
	if (true == GlobalValue::CurPlayer->GetIsMove())
	{
		if (false == RunActive_)
		{
			if (true == GlobalValue::CurPlayer->GetIsTown())
			{
				GlobalValue::CurPlayer->ChangeFSMState("Walk_Town");
			}
			else
			{
				GlobalValue::CurPlayer->ChangeFSMState("Walk_Field");
			}
		}
		else
		{
			GlobalValue::CurPlayer->ChangeFSMState("Run");
		}
	}
}

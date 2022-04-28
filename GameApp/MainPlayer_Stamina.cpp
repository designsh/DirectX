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

	// 스태미나 ProgressBar
	StaminaProgressBarRenderer_ = CreateTransformComponent<GameEngineProgressBarRenderer>(static_cast<int>(UIRenderOrder::UI11));
	StaminaProgressBarRenderer_->SetImage("StaminaBar.png");
	StaminaProgressBarRenderer_->SetProgressBarDirect(static_cast<int>(ProgressBarDirect::RightToLeft));
	StaminaProgressBarRenderer_->GetTransform()->SetLocalPosition(float4(-77.f, 18.f - ScreenHarfSize.y));

	// 스태미나 활성/비활성 버튼
	StaminaButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));
	StaminaButton_->CreateAnimation("Run_Default.png", "RunDefault", 0, 0, 0.1f, false);
	StaminaButton_->CreateAnimation("Run_Click.png", "RunClick", 0, 0, 0.1f, false);
	StaminaButton_->CreateAnimation("Walk_Default.png", "WalkDefault", 0, 0, 0.1f, false);
	StaminaButton_->CreateAnimation("Walk_Click.png", "WalkClick", 0, 0, 0.1f, false);
	StaminaButton_->GetTransform()->SetLocalScaling(float4(16.f, 20.f, 1.0f));
	StaminaButton_->GetTransform()->SetLocalPosition(float4(-138.f, 19.f - ScreenHarfSize.y));
	StaminaButton_->SetChangeAnimation("WalkDefault");

	// 스태미나 활성/비활성 버튼 충돌체
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
			// 버튼 상태 전환
			StaminaEnableOrDisabled();

			ButtonState_ = Button_State::Normal;
		}
	}

	// 스태미나 소모량 계산
	CalculationStaminaConsumption(_DeltaTime);

	// 스태미나 활성화버튼 충돌체크
	StaminaButtonCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_Stamina::StaminaActiveButtonClick, this, std::placeholders::_1));
}

void MainPlayer_Stamina::InitStaminaDrain()
{
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();
	StaminaDrain_ = static_cast<float>(PlayerInfo.RunStaminaDrain);
}

void MainPlayer_Stamina::CalculationStaminaConsumption(float _DeltaTime)
{
	// 메인플레이어가 존재할때
	if (nullptr != GlobalValue::CurPlayer)
	{
		// 메인플레이어가 뛰기상태이면 스태미나 소모량 계산
		if (true == GlobalValue::CurPlayer->GetIsRun())
		{
			// 플레이어가 현재 필드일때 소모
			if (false == GlobalValue::CurPlayer->GetIsTown())
			{
				// 이동중일때 소모
				if (true == GlobalValue::CurPlayer->GetIsMove())
				{
					// 시간에 따른 스태미나 소모
					if (0.f <= CurStamina_)
					{
						CurStamina_ -= (StaminaDrain_ * 0.01f) * _DeltaTime;
						StaminaProgressBarRenderer_->SetPercent(CurStamina_);

						// 스태미나량이 30%이하이면 스태미나 색을전환한다.
						if (0.3f >= CurStamina_ && false == Stamina30Percent_)
						{
							StaminaProgressBarRenderer_->SetResultColor(float4::RED);

							Stamina30Percent_ = true;
						}
					}

					// 스태미나량이 0%이하이면 플레이어는 걷기상태로 전환된다.
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
				else // 이동중이 아닐때
				{
					// 스태미나량이 100%가 아니라면 회복
					if (1.f >= CurStamina_)
					{
						// 스태미나량이 30% 이상이되면 색상(1,1,1,1)로 전환 및 색전환 Flag 해제
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
		else // 메인플레이어가 걷기상태일때
		{
			// 스태미나량이 100%가 아니라면 회복
			if (1.f >= CurStamina_)
			{
				// 스태미나량이 30% 이상이되면 색상(1,1,1,1)로 전환 및 색전환 Flag 해제
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
		// 플레이어 걷기/뛰기 Flag 전환
		GlobalValue::CurPlayer->SetIsRun(RunActive_);

		// 플레이어가 이동중이라면 상태바로전환
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
		// 현재 상태 체크에 따른 버튼 텍스쳐 전환
		if (false == RunActive_) // 걷기 -> 뛰기
		{
			StaminaButton_->SetChangeAnimation("WalkClick");

			RunActive_ = true;
		}
		else // 뛰기 -> 걷기
		{
			StaminaButton_->SetChangeAnimation("RunClick");

			RunActive_ = false;
		}

		ButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		// 현재 상태 체크에 따른 버튼 텍스쳐 전환
		if (false == RunActive_) // 현재 걷기 상태
		{
			StaminaButton_->SetChangeAnimation("WalkDefault");
		}
		else // 현재 뛰기상태
		{
			StaminaButton_->SetChangeAnimation("RunDefault");
		}
	}
}

void MainPlayer_Stamina::SetStaminaActive(bool _Flag)
{
	// Flag 저장
	RunActive_ = _Flag;

	// Flag에 따른 상태전환
	if (false == RunActive_) // 걷기상태라면
	{
		StaminaButton_->SetChangeAnimation("WalkDefault");
	}
	else // 뛰기상태라면
	{
		StaminaButton_->SetChangeAnimation("RunDefault");
	}

	// 플레이어가 이동중이라면 바로 상태전환
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

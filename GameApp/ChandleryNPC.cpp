#include "PreCompile.h"
#include "ChandleryNPC.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "TownMap.h"

#include "MainPlayer.h"
#include "NPC_MessageView.h"
#include "NPC_TopMenuBar.h"
#include "NPC_BuySellView.h"

bool ChandleryNPC::FirstInteraction = false;
bool ChandleryNPC::InteractionFlag = false;

bool ChandleryNPC::GetFirstInteaction()
{
	return FirstInteraction;
}

ChandleryNPC::ChandleryNPC() :
	ChandleryNPCRenderer_(nullptr),
	ChandleryNPCCollision_(nullptr),
	PrevMoveDir_(ChandleryNPC_MoveDir::DIR_L),
	CurMoveDir_(ChandleryNPC_MoveDir::DIR_L),
	PrevState_(ChandleryNPC_FSMState::ST_IDLE),
	CurState_(ChandleryNPC_FSMState::ST_IDLE),
	MoveDelayTime_(5.f),
	MoveSpeed_(100.f),
	MoveStartPos_(float4::ZERO),
	MoveCurPos_(float4::ZERO),
	MoveMinRange_(float4::ZERO),
	MoveMaxRange_(float4::ZERO),
	MessageView_(nullptr),
	TopMenuBar_(nullptr),
	SpeechSound_(nullptr)
{
}

ChandleryNPC::~ChandleryNPC()
{
}

void ChandleryNPC::Start()
{
	// ������ΰ��� ����
	InitChandleryNPC();

	// ������� ���� UI ����

	// 1. �޼���â(ȭ���߾ӻ�ܿ� ǥ��)
	MessageView_ = GetLevel()->CreateActor<NPC_MessageView>();
	MessageView_->Off();

	// 2. ��ܸ޴�(NPC ��ܿ� ǥ��)
	TopMenuBar_ = GetLevel()->CreateActor<NPC_TopMenuBar>();
	TopMenuBar_->GetTransform()->SetWorldPosition(GetTransform()->GetLocalPosition());
	TopMenuBar_->Off();

	// ���� ���� �÷��̾� ����
	SpeechSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void ChandleryNPC::Update(float _DeltaTime)
{
	// ���� ����
	State_.Update();

	float4 MyPos = GetTransform()->GetLocalPosition();
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	ChandleryNPCCollision_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// ���콺Ŭ������ ��ȣ�ۿ�����ȯ�õ� On�����϶�
	if (true == InteractionFlag)
	{
		InteractionDistanceCheck();
	}

	// ���콺�� �浹üũ
	ChandleryNPCCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&ChandleryNPC::MouseLButtonClick, this, std::placeholders::_1));

#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(ChandleryNPCCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

#pragma region ��ǥ���� Y�� ����
	float4 CurPos = GetTransform()->GetWorldPosition();
	TileIndex CurTileIndex = GlobalValue::TownMap->GetPosToTileIndex(float4(CurPos.x, CurPos.y - 53.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));
#pragma endregion
}

NPC_BuySellView* ChandleryNPC::GetChandleryShop()
{
	return TopMenuBar_->GetBuySellView();
}

void ChandleryNPC::MouseLButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// ���콺 ���ʹ�ư Ŭ������ �浹��
		// �����÷��̾�� ��ȣ�ۿ�Ÿ� üũ Flag On
		if (false == InteractionFlag)
		{
			InteractionFlag = true;
		}
	}
}

void ChandleryNPC::InteractionDistanceCheck()
{
	// �̵�&��� �����϶� �÷��̾���� �Ÿ� üũ
	if (CurState_ == ChandleryNPC_FSMState::ST_IDLE || CurState_ == ChandleryNPC_FSMState::ST_WALK)
	{
		// �Ÿ�üũ
		if (nullptr != GlobalValue::CurPlayer)
		{
			float4 MyPos = GetTransform()->GetLocalPosition();

			// �÷��̾ ���� ������ �˾Ƴ���.
			float4 PlayerPos = GlobalValue::CurPlayer->GetTransform()->GetLocalPosition() - float4(100.f, 100.f);

			// �κ���(�÷��̾�<->��ǥ����)�� ���� ���
			float4 MoveDirect = PlayerPos - MyPos;
			MoveDirect.Normalize3D();

			// �����̵����� �����̵����⿡ ����
			PrevMoveDir_ = CurMoveDir_;

			// ������ y����� ���⺤�͸� ���´�.
			float4 FrontVector = float4::UP;

			// �� ���͸� �����Ͽ� COS(��Ÿ) ������ ���
			float cosAngle = float4::DegreeDot3DToACosAngle(FrontVector, MoveDirect);

			float Angle = ((FrontVector.x * MoveDirect.y) - (FrontVector.y * MoveDirect.x) > 0.0f) ? cosAngle : -cosAngle;
			// ������ ���� ��ȯ(�� ���⺰ ���� : 30��)
			if (Angle < 0.0f) // ������
			{
				if (Angle > -60.f && Angle <= -30.f)
				{
					// ����
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_RT;
				}
				else if (Angle > -150.f && Angle <= -120.f)
				{
					// ���ϴ�
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_RB;
				}
				else if (Angle > -30.f && Angle <= 0.f)
				{
					// ���
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_T;
				}
				else if (Angle > -120.f && Angle <= -60.f)
				{
					// ���
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_R;
				}
				else if (Angle > -180.f && Angle <= -150.f)
				{
					// �ϴ�
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_B;
				}
			}
			else // ����
			{
				if (Angle > 30.f && Angle <= 60.f)
				{
					// �»��
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_LT;
				}
				else if (Angle > 120.f && Angle <= 150.f)
				{
					// ���ϴ�
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_LB;
				}
				else if (Angle > 0.f && Angle <= 30.f)
				{
					// ���
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_T;
				}
				else if (Angle > 60.f && Angle <= 120.f)
				{
					// �´�
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_L;
				}
				else if (Angle > 150.f && Angle <= 180.f)
				{
					// �ϴ�
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_B;
				}
			}

			// ��ȣ�ۿ�����·� ������ȯ
			State_.ChangeState("ChandleryNPC_CONVERSATION");
		}
	}
}

void ChandleryNPC::SetMoveRange()
{
	// ���ʻ��� ��ġ �������� �ش� NPC�� �̵����ɹ����� ��������.
	float4 MyPos = GetTransform()->GetLocalPosition();

	// �ּ��̵���ġ
	MoveMinRange_.x = MyPos.x - 150.f;
	MoveMinRange_.y = MyPos.y - 150.f;

	// �ִ��̵���ġ
	MoveMaxRange_.x = MyPos.x + 150.f;
	MoveMaxRange_.y = MyPos.y + 150.f;
}

void ChandleryNPC::SetMessageBoxText(const std::string& _Text)
{
	if (nullptr != MessageView_)
	{
		MessageView_->CreateNPCMessageTextList(_Text, NPCClassType::Akara);
	}
}

void ChandleryNPC::SetUIPosition()
{
	TopMenuBar_->GetTransform()->SetWorldPosition(GetTransform()->GetLocalPosition());
}

void ChandleryNPC::SetTopMenu()
{
	TopMenuBar_->CreateNPCTopMenu(NPCClassType::Akara, NPCType::PotionShop);
}

void ChandleryNPC::TopMenuBarInactive()
{
	TopMenuBar_->Off();
	TopMenuBar_->MenuButtonStateReset();
}

void ChandleryNPC::TopMenuBarActive()
{
	TopMenuBar_->On();
	TopMenuBar_->MenuButtonStateReset();
}

void ChandleryNPC::InteractionEnd()
{
	// �ܺο��� �ش� NPC ��ȣ�ۿ� ����� ȣ��Ǹ�,
	// ��ȣ�ۿ��� ����Ǿ����Ƿ� �ش� NPC�� �����·� �����Ѵ�.
	State_.ChangeState("ChandleryNPC_IDLE");
}

void ChandleryNPC::SelectConversationMenu()
{
	// ��ȣ�ۿ���¿��� ȭ�鿡 ǥ�õǴ� NPC��ܸ޴����� ��ȭ�޴� ���ý� ȣ��
	FirstInteraction = false;
	MessageView_->InteractionActive();

	// �ڱ�Ұ� ���� ���
	SpeechSound_->PlayAlone("Aka_Conversation.wav", 0);

	// ��ܸ޴� �ݱ�
	TopMenuBar_->Off();
}

bool ChandleryNPC::SpeechEndCheck()
{
	return SpeechSound_->IsPlay();
}

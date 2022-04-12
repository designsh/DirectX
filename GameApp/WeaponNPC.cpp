#include "PreCompile.h"
#include "WeaponNPC.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "NPC_MessageView.h"
#include "NPC_TopMenuBar.h"

bool WeaponNPC::FirstInteraction = false;
bool WeaponNPC::InteractionFlag = false;

bool WeaponNPC::GetFirstInteaction()
{
	return FirstInteraction;
}

WeaponNPC::WeaponNPC() :
	WeaponNPCRenderer_(nullptr),
	WeaponNPCCollision_(nullptr),
	PrevMoveDir_(WeaponNPC_MoveDir::DIR_L),
	CurMoveDir_(WeaponNPC_MoveDir::DIR_L),
	PrevState_(WeaponNPC_FSMState::ST_IDLE),
	CurState_(WeaponNPC_FSMState::ST_IDLE),
	MoveDelayTime_(5.f),
	InteractionDistance_(80.f),
	MoveSpeed_(100.f),
	MoveStartPos_(float4::ZERO),
	MoveCurPos_(float4::ZERO),
	MoveMinRange_(float4::ZERO),
	MoveMaxRange_(float4::ZERO),
	MessageView_(nullptr),
	TopMenuBar_(nullptr)
{
}

WeaponNPC::~WeaponNPC()
{
}

void WeaponNPC::Start()
{
	// ������ΰ��� ����
	InitWeaponNPC();

	// ������� ���� UI ����

	// 1. �޼���â(ȭ���߾ӻ�ܿ� ǥ��)
	MessageView_ = GetLevel()->CreateActor<NPC_MessageView>();
	MessageView_->Off();

	// 2. ��ܸ޴�(NPC ��ܿ� ǥ��)
	TopMenuBar_ = GetLevel()->CreateActor<NPC_TopMenuBar>();
	TopMenuBar_->Off();
}

void WeaponNPC::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(WeaponNPCCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// ���� ����
	State_.Update();

	// ���콺Ŭ������ ��ȣ�ۿ�����ȯ�õ� On�����϶�
	if (true == InteractionFlag)
	{
		InteractionDistanceCheck();
	}

	// ���콺�� �浹üũ
	WeaponNPCCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&WeaponNPC::MouseLButtonClick, this, std::placeholders::_1));
}

void WeaponNPC::MouseLButtonClick(GameEngineCollision* _Other)
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

void WeaponNPC::InteractionDistanceCheck()
{
	// �̵�&��� �����϶� �÷��̾���� �Ÿ� üũ
	if (CurState_ == WeaponNPC_FSMState::ST_IDLE || CurState_ == WeaponNPC_FSMState::ST_WALK)
	{
		// �Ÿ�üũ
		if (nullptr != GlobalValue::CurPlayer)
		{
			float4 MyPos = GetTransform()->GetLocalPosition();

			// �÷��̾ ���� ������ �˾Ƴ���.
			float4 PlayerPos = GlobalValue::CurPlayer->GetTransform()->GetLocalPosition();

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
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_RT;
				}
				else if (Angle > -150.f && Angle <= -120.f)
				{
					// ���ϴ�
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_RB;
				}
				else if (Angle > -30.f && Angle <= 0.f)
				{
					// ���
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_T;
				}
				else if (Angle > -120.f && Angle <= -60.f)
				{
					// ���
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_R;
				}
				else if (Angle > -180.f && Angle <= -150.f)
				{
					// �ϴ�
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_B;
				}
			}
			else // ����
			{
				if (Angle > 30.f && Angle <= 60.f)
				{
					// �»��
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_LT;
				}
				else if (Angle > 120.f && Angle <= 150.f)
				{
					// ���ϴ�
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_LB;
				}
				else if (Angle > 0.f && Angle <= 30.f)
				{
					// ���
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_T;
				}
				else if (Angle > 60.f && Angle <= 120.f)
				{
					// �´�
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_L;
				}
				else if (Angle > 150.f && Angle <= 180.f)
				{
					// �ϴ�
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_B;
				}
			}

			// ��ȣ�ۿ�����·� ������ȯ
			State_.ChangeState("WeaponNPC_CONVERSATION");
		}
	}
}

void WeaponNPC::SetMoveRange()
{
	// ���ʻ��� ��ġ �������� �ش� NPC�� �̵����ɹ����� ��������.
	float4 MyPos = GetTransform()->GetLocalPosition();

	// �ּ��̵���ġ
	MoveMinRange_.x = MyPos.x - 200.f;
	MoveMinRange_.y = MyPos.y - 200.f;

	// �ִ��̵���ġ
	MoveMaxRange_.x = MyPos.x + 200.f;
	MoveMaxRange_.y = MyPos.y + 200.f;
}

void WeaponNPC::SetMessageBoxText(const std::string& _Text)
{
	if (nullptr != MessageView_)
	{
		MessageView_->CreateNPCMessageTextList(_Text);
	}
}

void WeaponNPC::SetUIPosition()
{
	TopMenuBar_->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
}

void WeaponNPC::SetTopMenu()
{

	TopMenuBar_->CreateNPCTopMenu(NPCClassType::Charsi, NPCType::WeaponShop);
}

void WeaponNPC::InteractionEnd()
{
	// �ܺο��� �ش� NPC ��ȣ�ۿ� ����� ȣ��Ǹ�,
	// ��ȣ�ۿ��� ����Ǿ����Ƿ� �ش� NPC�� �����·� �����Ѵ�.
	State_.ChangeState("WeaponNPC_IDLE");
}

void WeaponNPC::SelectConversationMenu()
{
	// ��ȣ�ۿ���¿��� ȭ�鿡 ǥ�õǴ� NPC��ܸ޴����� ��ȭ�޴� ���ý� ȣ��
	FirstInteraction = false;
	MessageView_->InteractionActive();

	// ��ܸ޴� �ݱ�
	TopMenuBar_->Off();
}

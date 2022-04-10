#include "PreCompile.h"
#include "WeaponNPC.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

bool WeaponNPC::FirstInteraction = false;
bool WeaponNPC::InteractionFlag = false;

bool WeaponNPC::GetFirstInteaction()
{
	return FirstInteraction;
}

WeaponNPC::WeaponNPC() :
	WeaponNPCRenderer_(nullptr),
	WeaponNPCCollision_(nullptr),
	PrevMoveDir_(WeaponNPC_MoveDir::DIR_B),
	CurMoveDir_(WeaponNPC_MoveDir::DIR_B),
	PrevState_(WeaponNPC_FSMState::ST_IDLE),
	CurState_(WeaponNPC_FSMState::ST_IDLE),
	MoveDelayTime_(3.f),
	InteractionDistance_(80.f),
	TargetMovePos_(float4(100.f, 0.f))
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



}

void WeaponNPC::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(WeaponNPCCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// ���� ����
	State_.Update();

	// ���콺Ŭ������ ��ȣ�ۿ� üũ On�����϶�
	if (true == InteractionFlag)
	{
		// �̵�&��� �����϶� �÷��̾���� �Ÿ� üũ
		if (CurState_ == WeaponNPC_FSMState::ST_IDLE || CurState_ == WeaponNPC_FSMState::ST_WALK)
		{
			// �Ÿ�üũ


			// ���������Ÿ��� ���Խ� �÷��̾� �������� ���������ȯ ��


			// ��ȣ�ۿ����� ������ȯ
			//State_.ChangeState("WeaponNPC_CONVERSATION");
		}
	}

	// ���콺�� �浹üũ
	WeaponNPCCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&WeaponNPC::InteractionCheck, this, std::placeholders::_1));
}

void WeaponNPC::InteractionCheck(GameEngineCollision* _Other)
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

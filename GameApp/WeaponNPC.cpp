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
	// 무기상인관련 생성
	InitWeaponNPC();

	// 무기상인 관련 UI 생성



}

void WeaponNPC::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(WeaponNPCCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// 상태 갱신
	State_.Update();

	// 마우스클릭으로 상호작용 체크 On상태일때
	if (true == InteractionFlag)
	{
		// 이동&대기 상태일때 플레이어와의 거리 체크
		if (CurState_ == WeaponNPC_FSMState::ST_IDLE || CurState_ == WeaponNPC_FSMState::ST_WALK)
		{
			// 거리체크


			// 일정사정거리에 진입시 플레이어 방향으로 현재방향전환 후


			// 상호작용으로 상태전환
			//State_.ChangeState("WeaponNPC_CONVERSATION");
		}
	}

	// 마우스와 충돌체크
	WeaponNPCCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&WeaponNPC::InteractionCheck, this, std::placeholders::_1));
}

void WeaponNPC::InteractionCheck(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 마우스 왼쪽버튼 클릭으로 충돌시
		// 현재플레이어와 상호작용거리 체크 Flag On
		if (false == InteractionFlag)
		{
			InteractionFlag = true;
		}
	}
}

#include "PreCompile.h"
#include "WeaponNPC.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "NPC_MessageView.h"

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
	MoveDelayTime_(3.f),
	InteractionDistance_(80.f),
	MoveSpeed_(100.f),
	MoveStartPos_(float4::ZERO),
	MoveCurPos_(float4::ZERO),
	MessageView_(nullptr)
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

	// 마우스클릭으로 상호작용대기전환시도 On상태일때
	if (true == InteractionFlag)
	{
		InteractionDistanceCheck();
	}

	// 마우스와 충돌체크
	WeaponNPCCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&WeaponNPC::MouseLButtonClick, this, std::placeholders::_1));
}

void WeaponNPC::MouseLButtonClick(GameEngineCollision* _Other)
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

void WeaponNPC::InteractionDistanceCheck()
{
	// 이동&대기 상태일때 플레이어와의 거리 체크
	if (CurState_ == WeaponNPC_FSMState::ST_IDLE || CurState_ == WeaponNPC_FSMState::ST_WALK)
	{
		// 거리체크
		if (nullptr != GlobalValue::CurPlayer)
		{
			float4 MyPos = GetTransform()->GetLocalPosition();

			// 플레이어를 향한 방향을 알아낸다.
			float4 PlayerPos = GlobalValue::CurPlayer->GetTransform()->GetLocalPosition();

			// 두벡터(플레이어<->목표지점)의 각도 계산
			float4 MoveDirect = PlayerPos - MyPos;
			MoveDirect.Normalize3D();

			// 현재이동방향 이전이동방향에 저장
			PrevMoveDir_ = CurMoveDir_;

			// 월드의 y축기준 방향벡터를 얻어온다.
			float4 FrontVector = float4::UP;

			// 두 벡터를 내적하여 COS(세타) 각도를 계산
			float cosAngle = float4::DegreeDot3DToACosAngle(FrontVector, MoveDirect);

			float Angle = ((FrontVector.x * MoveDirect.y) - (FrontVector.y * MoveDirect.x) > 0.0f) ? cosAngle : -cosAngle;
			// 각도별 방향 전환(각 방향별 범위 : 30도)
			if (Angle < 0.0f) // 오른쪽
			{
				if (Angle > -60.f && Angle <= -30.f)
				{
					// 우상단
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_RT;
				}
				else if (Angle > -150.f && Angle <= -120.f)
				{
					// 우하단
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_RB;
				}
				else if (Angle > -30.f && Angle <= 0.f)
				{
					// 상단
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_T;
				}
				else if (Angle > -120.f && Angle <= -60.f)
				{
					// 우단
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_R;
				}
				else if (Angle > -180.f && Angle <= -150.f)
				{
					// 하단
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_B;
				}
			}
			else // 왼쪽
			{
				if (Angle > 30.f && Angle <= 60.f)
				{
					// 좌상단
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_LT;
				}
				else if (Angle > 120.f && Angle <= 150.f)
				{
					// 좌하단
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_LB;
				}
				else if (Angle > 0.f && Angle <= 30.f)
				{
					// 상단
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_T;
				}
				else if (Angle > 60.f && Angle <= 120.f)
				{
					// 좌단
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_L;
				}
				else if (Angle > 150.f && Angle <= 180.f)
				{
					// 하단
					CurMoveDir_ = WeaponNPC_MoveDir::DIR_B;
				}
			}

			// 상호작용대기상태로 상태전환
			State_.ChangeState("WeaponNPC_CONVERSATION");
		}
	}
}

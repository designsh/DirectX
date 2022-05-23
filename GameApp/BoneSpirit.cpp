#include "PreCompile.h"
#include "BoneSpirit.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"
#include "CatacombsMap.h"

#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"
#include "Andariel.h"

int BoneSpirit::ProjetileCount = 0;;

BoneSpirit::BoneSpirit() :
	Renderer_(nullptr),
	Collider_(nullptr),
	State_(),
	BonsSpiritInfo_{},
	CurDir_(BoneSpirit_Dir::BS_L),
	StartPos_(float4::ZERO),
	MouseClickPos_(float4::ZERO),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(200.f),
	NavigationIndex_(-1),
	FireStart_(false),
	Targeting_(false),
	Damage_(0),
	TargetMonster_(nullptr)
{
	NavigationIndex_ = ProjetileCount;
	++ProjetileCount;
}

BoneSpirit::~BoneSpirit()
{
}

void BoneSpirit::Start()
{
}

void BoneSpirit::Update(float _DeltaTime)
{
	if (true == FireStart_)
	{
		// 충돌체크
		if (nullptr != Collider_)
		{
#ifdef _DEBUG
			GetLevel()->UIPushDebugRender(Collider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

			Collider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Monster), std::bind(&BoneSpirit::TargetCollision, this, std::placeholders::_1));
		}

		// 상태 업데이트
		State_.Update();

		// Z Order 갱신
		TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 50.f));
		GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 22.f);
	}
}

void BoneSpirit::TargetCollision(GameEngineCollision* _Other)
{
	// 타겟팅일경우 타겟과의 충돌시에 타격을 입히고,
	if (true == Targeting_)
	{
		// 타겟몬스터시 충돌성공 처리
		if (TargetMonster_ == _Other->GetActor())
		{
			// 상태 전환
			State_.ChangeState("Explode");
			
			// 타겟과 충돌시 타겟에게 데미지를 입히며
			std::string CollisionName = _Other->GetActor()->GetName();
			if (std::string::npos != CollisionName.find("Fallen"))
			{
				Fallen* CurAttackMonster = (Fallen*)_Other->GetActor();
				if (Fallen_FSMState::FL_DEAD != CurAttackMonster->GetCurState() &&
					Fallen_FSMState::FL_DEATH != CurAttackMonster->GetCurState())
				{
					CurAttackMonster->GetHitDamage(Damage_);
				}
			}
			else if (std::string::npos != CollisionName.find("SpikeFiend"))
			{
				SpikeFiend* CurAttackMonster = (SpikeFiend*)_Other->GetActor();
				if (SpikeFiend_FSMState::SF_DEAD != CurAttackMonster->GetCurState() &&
					SpikeFiend_FSMState::SF_DEATH != CurAttackMonster->GetCurState())
				{
					CurAttackMonster->GetHitDamage(Damage_);
				}
			}
			else if (std::string::npos != CollisionName.find("Tainted"))
			{
				Tainted* CurAttackMonster = (Tainted*)_Other->GetActor();
				if (Tainted_FSMState::ST_DEAD != CurAttackMonster->GetCurState() && 
					Tainted_FSMState::ST_DEATH != CurAttackMonster->GetCurState())
				{
					CurAttackMonster->GetHitDamage(Damage_);
				}
			}
			else if (std::string::npos != CollisionName.find("Zombie"))
			{
				Zombie* CurAttackMonster = (Zombie*)_Other->GetActor();

			}
			else if (std::string::npos != CollisionName.find("Andariel"))
			{
				Andariel* CurAttackMonster = (Andariel*)_Other->GetActor();

			}
		}
	}
	// 논타겟팅일경우 어떠한 몬스터이든 충돌시 해당 몬스터에게 타겟을 입힌다.
	else
	{
		// 상태 전환
		State_.ChangeState("Explode");
		
		// 타겟과 충돌시 타겟에게 데미지를 입히며
		std::string CollisionName = _Other->GetActor()->GetName();
		if (std::string::npos != CollisionName.find("Fallen"))
		{
			Fallen* CurAttackMonster = (Fallen*)_Other->GetActor();
			if (Fallen_FSMState::FL_DEAD != CurAttackMonster->GetCurState() &&
				Fallen_FSMState::FL_DEATH != CurAttackMonster->GetCurState())
			{
				CurAttackMonster->GetHitDamage(Damage_);
			}
		}
		else if (std::string::npos != CollisionName.find("SpikeFiend"))
		{
			SpikeFiend* CurAttackMonster = (SpikeFiend*)_Other->GetActor();
			if (SpikeFiend_FSMState::SF_DEAD != CurAttackMonster->GetCurState() &&
				SpikeFiend_FSMState::SF_DEATH != CurAttackMonster->GetCurState())
			{
				CurAttackMonster->GetHitDamage(Damage_);
			}
		}
		else if (std::string::npos != CollisionName.find("Tainted"))
		{
			Tainted* CurAttackMonster = (Tainted*)_Other->GetActor();
			if (Tainted_FSMState::ST_DEAD != CurAttackMonster->GetCurState() &&
				Tainted_FSMState::ST_DEATH != CurAttackMonster->GetCurState())
			{
				CurAttackMonster->GetHitDamage(Damage_);
			}
		}
		else if (std::string::npos != CollisionName.find("Zombie"))
		{
			Zombie* CurAttackMonster = (Zombie*)_Other->GetActor();

		}
		else if (std::string::npos != CollisionName.find("Andariel"))
		{
			Andariel* CurAttackMonster = (Andariel*)_Other->GetActor();

		}
	}
}

void BoneSpirit::BoneSpiritFire(const float4& _StartPos, const float4& _MouseClickPos, GameEngineActor* _TargetingMonster)
{
	// 마우스 클릭지점으로 발사 후 진행방향에 몬스터와 충돌시 타격을 입히고 소멸
	TargetMonster_ = _TargetingMonster;
	
	// 논타겟팅
	if (nullptr == TargetMonster_)
	{
		Targeting_ = false;
	}
	// 타겟팅
	else
	{
		Targeting_ = true;
	}

	StartPos_ = _StartPos;
	MouseClickPos_ = _MouseClickPos + GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();

	// 데미지 등록
	MainPlayerInfomation::GetInst().GetSkillInfo(93, BonsSpiritInfo_);
	Damage_ = BonsSpiritInfo_.SkillDamage;
	
	// 네비게이션 생성
	GlobalValue::CatacombsMap->CreateNavitaion(NavigationObjectType::Player_ProjectileSkill, ProjetileCount);

	// 애니메이션 생성
	CreateAnimation();

	// 충돌체 생성
	CreateCollision();

	// FSM 생성
	CreateFSMState();

	// 위치 셋팅
	GetTransform()->SetWorldPosition(StartPos_);

	// 시작
	State_.ChangeState("Move");

	// 발사 시작
	FireStart_ = true;
}

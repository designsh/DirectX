#include "PreCompile.h"
#include "Andariel.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineCore.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"
#include "MainPlayer.h"
#include "CatacombsMap.h"

#include "Portal.h"

#include "AndarielProjectile.h"
#include "AndarielDeathEffect.h"

int Andariel::AndarielCnt = 0;

Andariel::Andariel() :
	Andariel_(nullptr),
	AndarielEffect_(nullptr),
	BodyCollider_(nullptr),
	SpawnRoomNo_(-1),
	SpawnTile_(),
	IdleDelayTime_(1.f),
	NavigationIndex_(-1),
	SkillDelayTime_(15.f),
	SkillAttack_(false),
	ProjectileCnt_(0),
	ProjectileStartDir_(float4::ZERO),
	Attack_(false),
	MonsterInfo_(),
	CurHP_(0),
	MapHP_(0),
	DropGold_(0),
	State_(),
	PrevState_(Andariel_FSMState::AD_ROOMDETECT),
	CurState_(Andariel_FSMState::AD_ROOMDETECT),
	MoveTargetTile_(),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(150.f),
	PrevDir_(Andariel_TargetDir::AD_B),
	CurDir_(Andariel_TargetDir::AD_B)
{
	NavigationIndex_ = AndarielCnt;
	++AndarielCnt;
}

Andariel::~Andariel()
{
}

void Andariel::Start()
{
	// �ش� ���Ͱ��� �ʱ�ȭ
	InitAndariel();
}

void Andariel::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// ���� ����
	State_.Update();

	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));

	// ��ų��Ÿ�� �Ҹ�
	// ��, ��ü�����̰ų� ��������̸� ��Ÿ�� �Ҹ����
	if (Andariel_FSMState::AD_DEATH != CurState_ && 
		Andariel_FSMState::AD_DEAD != CurState_ &&
		Andariel_FSMState::AD_ROOMDETECT != CurState_)
	{
		if (false == SkillAttack_)
		{
			SkillDelayTime_ -= _DeltaTime;
			if (0.f >= SkillDelayTime_)
			{
				SkillAttack_ = true;
				SkillDelayTime_ = 15.f;
			}
		}
	}

	// �浹ü ��ġ ����
	float4 MyPos = float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y, 0.f);
	float4 CamPos = float4(GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().x, GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().y, 0.f);
	BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// �浹ó��(���콺�� �浹ó��)
	BodyCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Andariel::MouseCollision, this, std::placeholders::_1));

	// ���ݻ����϶� Ÿ�ٰ� �����浹�̶�� Ÿ�ٿ��� ���ظ� ����
	if (Andariel_FSMState::AD_ATTACK == CurState_)
	{
		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&Andariel::EnemyCollision, this, std::placeholders::_1));
	}
}

#pragma region EnemyCheck List Function
// �� ���� üũ ����Ʈ
void Andariel::SetEnterTheRoomDetectList(int _SpawnRoomNo)
{
	// �������� �⺻���� ����
	SpawnRoomNo_ = _SpawnRoomNo;
	if (-1 != SpawnRoomNo_)
	{
		SpawnTile_ = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());

		// ���� ���� ������ ���� �ٴ�Ÿ�� ���� ��Ÿ���� ��� ���� ������� �ۼ�
		int RoomTileListCnt = static_cast<int>(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_.size());
		RoomTileList_.clear();
		for (int i = 0; i < RoomTileListCnt; ++i)
		{
			// �ٴ�Ÿ���� ��ġ Get
			float4 FloorCenterPos = GlobalValue::CatacombsMap->GetFloorTileIndexToPos(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_[i]);

			// �ٴ�Ÿ�� 1�� ���� 3x3�� ��Ÿ���� ������.
			TileIndex WallTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(FloorCenterPos);
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					RoomTileList_.push_back(WallTileIndex);
					WallTileIndex.X_ += 1;
				}

				WallTileIndex.X_ = GlobalValue::CatacombsMap->GetWallTileIndex(FloorCenterPos).X_;
				WallTileIndex.Y_ += 1;
			}
		}
	}
}

bool Andariel::EnterTheRoomDetectCheck()
{
	TileIndex PlayerTile = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	for (auto& CheckTile : RoomTileList_)
	{
		if (CheckTile == PlayerTile)
		{
			return true;
		}
	}

	return false;
}

#pragma endregion

#pragma region AnimationEnd Callback Function
void Andariel::AttackEnd()
{
	// ������ ��ȯ
	State_.ChangeState("Idle");
}

void Andariel::SkillAttackEnd()
{
	// ������ ��ȯ
	State_.ChangeState("Idle");
}

void Andariel::DeathEnd()
{
	// ��ü���� ��ȯ
	State_.ChangeState("Dead");
}

#pragma endregion

#pragma region AnimationFrame Callback Function
void Andariel::ProjectileFire()
{
	if (10 <= ProjectileCnt_)
	{
		return;
	}

	float4 MoveDir = float4::ZERO;

	// ���� ���۹������
	if (0 == ProjectileCnt_)
	{
		// �÷��̾ �ٶ󺸴� ���⺤�͸� -45�� ȸ����Ų ���⺤�͸� �ʱⰪ���� ����
		float4 Direct = (GlobalValue::CurPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition()).NormalizeReturn3D();
		Direct.RotateZDegree(-45.f);
		ProjectileStartDir_ = Direct;
		MoveDir = ProjectileStartDir_;
	}
	// �̵����� ����
	else
	{
		// ���۹��⺤�͸� 9����ȸ�����Ѽ� �߻�ü�� �̵����⺤�͸� ����Ѵ�.
		// ������⺤�� ~ 90��ȸ�� �̵����⺤�͸� ������.
		ProjectileStartDir_.RotateZDegree(9.f);
		MoveDir = ProjectileStartDir_;
	}

	// �߻�ü ����(�Ҹ�ð� ���� - 5��)
	AndarielProjectile* NewProjectile = GetLevel()->CreateActor<AndarielProjectile>();
	NewProjectile->GetTransform()->SetWorldPosition(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y));
	NewProjectile->SkillAttackProjectile(static_cast<int>(CurDir_), MoveDir, MonsterInfo_.Damage);
	NewProjectile->Release(5.f);

	// �߻�ü ����ī��Ʈ ����(�� 10�� ����)
	++ProjectileCnt_;
}

void Andariel::DeathEffectStart()
{
	// �� ���⺰ ������ 3�����ӿ� ȣ��Ǹ� ��� ����Ʈ�� ����
	// => ������ ��ü �Ҳ�, �̵��Ҳ�, ī�޶���ŷȿ��
	// => ��ü�Ҳ� �ִϸ��̼������ ����Ʈ ���, ī�޶���ŷ�ߴ�, ���� ���, �����ڸ��� ��Ż����(���������̵���)
	AndarielDeathEffect* DeathEffect = GetLevel()->CreateActor<AndarielDeathEffect>();
	DeathEffect->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	DeathEffect->GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));
	DeathEffect->CreateDeathFire();
}

#pragma endregion

#pragma region �ܺ����� ����������ȯ
void Andariel::SpawnToDeath()
{
	// ��ų���������� ����Ϸ��� ��ü�� ����
	// => ������ ���ÿ� ���ó��
	CurHP_ = 0;
	State_.ChangeState("Death");
}

void Andariel::GetHitDamage(int _Damage)
{
	CurHP_ -= _Damage;
	if (0 >= CurHP_)
	{
		CurHP_ = 0;
		State_.ChangeState("Death");
	}
	else
	{
		State_.ChangeState("GetHit");
	}
}

#pragma endregion

#pragma region ������ ���
void Andariel::PortalSpawnAfterDeath()
{
	// ���� �����ڸ��� ��Ż���� ��
	GameEngineLevel* NextLevel = GameEngineCore::LevelFind("EndingLevel");
	Portal* EndingPortal = GetLevel()->CreateActor<Portal>(static_cast<int>(UpdateOrder::OBJECT));
	EndingPortal->GetTransform()->SetWorldPosition(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y, 0.f));
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	EndingPortal->GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));
	EndingPortal->CreateLevelChangePortal(PortalType::TOWN, NextLevel);
	GlobalValue::Portal = EndingPortal;

	// ���� �״´�.
	Death();

	// ���� �ʱ�ȭ
	GlobalValue::Andariel = nullptr;
}

#pragma endregion

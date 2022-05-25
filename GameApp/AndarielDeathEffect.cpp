#include "PreCompile.h"
#include "AndarielDeathEffect.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "CatacombsMap.h"
#include "Andariel.h"

AndarielDeathEffect::AndarielDeathEffect() :
	DeathFire_(nullptr),
	CamShakeStart_(false),
	Shake_(false),
	ShakeDelayTime_(0.001f),
	InitCamPos_(float4::ZERO),
	CurMoveDeathFireDir_(),
	MoveDeathFireSpawn_(false),
	MoveDeathFireSpawnCnt_(5),
	MoveDeathFireSpawnTime_(5.f)
{
}

AndarielDeathEffect::~AndarielDeathEffect()
{
}

void AndarielDeathEffect::Start()
{
	// 해당 이펙트관련 초기화
	InitDeathEffect();

	InitCamPos_ = GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
}

void AndarielDeathEffect::Update(float _DeltaTime)
{
	if (true == CamShakeStart_)
	{
		ShakeDelayTime_ -= _DeltaTime;
		if (0.f >= ShakeDelayTime_)
		{
			CamShakeEffect();
			ShakeDelayTime_ = 0.001f;
		}
	}

	// 이동용 불꽃 생성
	if (true == MoveDeathFireSpawn_)
	{
		MoveDeathFireSpawnTime_ -= _DeltaTime;
		if (0.f >= MoveDeathFireSpawnTime_)
		{
			MoveDeathFireSpawn();
			MoveDeathFireSpawnTime_ = 5.f;
		}

		// 최대 생성갯수 넘어가면 더이상 스폰하지않는다.
		if (5 <= MoveDeathFireSpawnCnt_)
		{
			MoveDeathFireSpawn_ = false;
		}
	}
}

void AndarielDeathEffect::CreateDeathFire()
{
	// 카메라 쉐이킹효과 발생
	CamShakeStart_ = true;

	// 보스사망본체 불꽃 발생
	CreateAnimation();
}

void AndarielDeathEffect::NormalDeathFire1()
{
	// 애니메이션 변경
	DeathFire_->SetChangeAnimation("Fire2");

	// 랜덤방향 이동 불꽃 생성 Flag
	MoveDeathFireSpawn_ = true;

	// 관리목록 초기화
	MoveDeathFireList_.clear();
}

void AndarielDeathEffect::NormalDeathFire2()
{
	// 애니메이션 변경
	DeathFire_->SetChangeAnimation("Fire3");
}

void AndarielDeathEffect::NormalDeathFire3()
{
	if (true == CamShakeStart_)
	{
		// 해당 애니메이션 종료시 카메라 쉐이킹 효과를 중단하며
		CamShakeStart_ = false;

		// 보스는 실질적으로 사망처리하면서 해당 자리에 포탈생성
		if (nullptr != GlobalValue::Andariel)
		{
			GlobalValue::Andariel->PortalSpawnAfterDeath();
		}

		// 사망처리
		Death();
	}
}

void AndarielDeathEffect::DirDeathFireFrameCallback()
{
	// 이동후 새로운 불꽃 발생

}

void AndarielDeathEffect::DirDeathFireEndCallback()
{
	// 애니메이션 종료시 해당 렌더러 사망

}

void AndarielDeathEffect::CamShakeEffect()
{
	// 카메라 흔들림
	if (false == Shake_)
	{
		GameEngineRandom ShakeRandom;
		CamShakeDir Dir = static_cast<CamShakeDir>(ShakeRandom.RandomInt(0, 7));
		switch (Dir)
		{
		case CamShakeDir::CS_B:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(0.f, -10.f));
			break;
		case CamShakeDir::CS_LB:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(-10.f, -10.f));
			break;
		case CamShakeDir::CS_L:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(-10.f, 0.f));
			break;
		case CamShakeDir::CS_LT:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(-10.f, 10.f));
			break;
		case CamShakeDir::CS_T:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(0.f, 10.f));
			break;
		case CamShakeDir::CS_RT:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(10.f, 10.f));
			break;
		case CamShakeDir::CS_R:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(10.f, 0.f));
			break;
		case CamShakeDir::CS_RB:
			GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_ + float4(10.f, -10.f));
			break;
		}
		Shake_ = true;
	}
	else
	{
		// 원래자리 복귀
		GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_);
		Shake_ = false;
	}
}

void AndarielDeathEffect::MoveDeathFireSpawn()
{
	// 위치계산
	TileIndex BodyTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());
	GameEngineRandom DirRandom;
	MoveDeathFireDir MoveDir = static_cast<MoveDeathFireDir>(DirRandom.RandomInt(0, 7));
	switch (MoveDir)
	{
		case MoveDeathFireDir::DIR_T:
		{
			BodyTileIndex = BodyTileIndex + TileIndex(-1, 0);
			break;
		}
		case MoveDeathFireDir::DIR_RT:
		{
			BodyTileIndex = BodyTileIndex + TileIndex(-1, -1);
			break;
		}
		case MoveDeathFireDir::DIR_R:
		{
			BodyTileIndex = BodyTileIndex + TileIndex(0, -1);
			break;
		}
		case MoveDeathFireDir::DIR_RB:
		{
			BodyTileIndex = BodyTileIndex + TileIndex(1, -1);
			break;
		}
		case MoveDeathFireDir::DIR_B:
		{
			BodyTileIndex = BodyTileIndex + TileIndex(1, 0);
			break;
		}
		case MoveDeathFireDir::DIR_LB:
		{
			BodyTileIndex = BodyTileIndex + TileIndex(1, 1);
			break;
		}
		case MoveDeathFireDir::DIR_L:
		{
			BodyTileIndex = BodyTileIndex + TileIndex(0, 1);
			break;
		}
		case MoveDeathFireDir::DIR_LT:
		{
			BodyTileIndex = BodyTileIndex + TileIndex(-1, 1);
			break;
		}
	}

	GameEngineImageRenderer* MoveDeathFire_ = CreateTransformComponent<GameEngineImageRenderer>();
	MoveDeathFire_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
	MoveDeathFire_->GetTransform()->SetWorldPosition(GlobalValue::CatacombsMap->GetWallTileIndexToPos(BodyTileIndex));
	MoveDeathFire_->SetRenderingPipeLine("TextureTrans");

	MoveDeathFire_->CreateAnimation("DeathFireDir.png", "MoveDeathFire", 0, 19, 0.1f, false);
	MoveDeathFire_->SetChangeAnimation("MoveDeathFire");

	// 종료시 호출함수 등록
	MoveDeathFire_->SetFrameCallBack("MoveDeathFire", 10, std::bind(&AndarielDeathEffect::DirDeathFireEndCallback, this));
	MoveDeathFire_->SetEndCallBack("MoveDeathFire", std::bind(&AndarielDeathEffect::DirDeathFireFrameCallback, this));

	// 관리목록에 추가
	MoveDeathFireList_.push_back(MoveDeathFire_);

	// 스폰카운트증가
	++MoveDeathFireSpawnCnt_;
}

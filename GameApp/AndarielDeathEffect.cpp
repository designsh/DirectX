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
	// �ش� ����Ʈ���� �ʱ�ȭ
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

	// �̵��� �Ҳ� ����
	if (true == MoveDeathFireSpawn_)
	{
		MoveDeathFireSpawnTime_ -= _DeltaTime;
		if (0.f >= MoveDeathFireSpawnTime_)
		{
			MoveDeathFireSpawn();
			MoveDeathFireSpawnTime_ = 5.f;
		}

		// �ִ� �������� �Ѿ�� ���̻� ���������ʴ´�.
		if (5 <= MoveDeathFireSpawnCnt_)
		{
			MoveDeathFireSpawn_ = false;
		}
	}
}

void AndarielDeathEffect::CreateDeathFire()
{
	// ī�޶� ����ŷȿ�� �߻�
	CamShakeStart_ = true;

	// ���������ü �Ҳ� �߻�
	CreateAnimation();
}

void AndarielDeathEffect::NormalDeathFire1()
{
	// �ִϸ��̼� ����
	DeathFire_->SetChangeAnimation("Fire2");

	// �������� �̵� �Ҳ� ���� Flag
	MoveDeathFireSpawn_ = true;

	// ������� �ʱ�ȭ
	MoveDeathFireList_.clear();
}

void AndarielDeathEffect::NormalDeathFire2()
{
	// �ִϸ��̼� ����
	DeathFire_->SetChangeAnimation("Fire3");
}

void AndarielDeathEffect::NormalDeathFire3()
{
	if (true == CamShakeStart_)
	{
		// �ش� �ִϸ��̼� ����� ī�޶� ����ŷ ȿ���� �ߴ��ϸ�
		CamShakeStart_ = false;

		// ������ ���������� ���ó���ϸ鼭 �ش� �ڸ��� ��Ż����
		if (nullptr != GlobalValue::Andariel)
		{
			GlobalValue::Andariel->PortalSpawnAfterDeath();
		}

		// ���ó��
		Death();
	}
}

void AndarielDeathEffect::DirDeathFireFrameCallback()
{
	// �̵��� ���ο� �Ҳ� �߻�

}

void AndarielDeathEffect::DirDeathFireEndCallback()
{
	// �ִϸ��̼� ����� �ش� ������ ���

}

void AndarielDeathEffect::CamShakeEffect()
{
	// ī�޶� ��鸲
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
		// �����ڸ� ����
		GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(InitCamPos_);
		Shake_ = false;
	}
}

void AndarielDeathEffect::MoveDeathFireSpawn()
{
	// ��ġ���
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

	// ����� ȣ���Լ� ���
	MoveDeathFire_->SetFrameCallBack("MoveDeathFire", 10, std::bind(&AndarielDeathEffect::DirDeathFireEndCallback, this));
	MoveDeathFire_->SetEndCallBack("MoveDeathFire", std::bind(&AndarielDeathEffect::DirDeathFireFrameCallback, this));

	// ������Ͽ� �߰�
	MoveDeathFireList_.push_back(MoveDeathFire_);

	// ����ī��Ʈ����
	++MoveDeathFireSpawnCnt_;
}

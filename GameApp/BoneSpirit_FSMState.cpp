#include "PreCompile.h"
#include "BoneSpirit.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "CatacombsMap.h"
#include "MainPlayer.h"

void BoneSpirit::TargetDirCheckAndAnimationSetting(const float4& _TargetPos, const std::string& _StateName)
{
	float4 Direct = _TargetPos - GetTransform()->GetWorldPosition();
	Direct.Normalize3D();

	float4 FrontVector = float4::UP;
	float cosAngle = float4::DegreeDot3DToACosAngle(FrontVector, Direct);

	float Angle = ((FrontVector.x * Direct.y) - (FrontVector.y * Direct.x) > 0.0f) ? cosAngle : -cosAngle;
	if (Angle < 0.0f) // 오른쪽
	{
		if (Angle > -60.f && Angle <= -30.f)
		{
			// 우상단
			CurDir_ = BoneSpirit_Dir::BS_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// 우하단
			CurDir_ = BoneSpirit_Dir::BS_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// 상단
			CurDir_ = BoneSpirit_Dir::BS_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// 우단
			CurDir_ = BoneSpirit_Dir::BS_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// 하단
			CurDir_ = BoneSpirit_Dir::BS_B;
		}
	}
	else // 왼쪽
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// 좌상단
			CurDir_ = BoneSpirit_Dir::BS_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// 좌하단
			CurDir_ = BoneSpirit_Dir::BS_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// 상단
			CurDir_ = BoneSpirit_Dir::BS_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// 좌단
			CurDir_ = BoneSpirit_Dir::BS_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// 하단
			CurDir_ = BoneSpirit_Dir::BS_B;
		}
	}

	// 애니메이션 변경
	AnimationChangeCheck(_StateName);
}

void BoneSpirit::AnimationChangeCheck(const std::string& _StateName)
{
	std::string AnimationName = _StateName;

	switch (CurDir_)
	{
		case BoneSpirit_Dir::BS_LB:
		{
			AnimationName += "_LB";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case BoneSpirit_Dir::BS_LT:
		{
			AnimationName += "_LT";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case BoneSpirit_Dir::BS_RT:
		{
			AnimationName += "_RT";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case BoneSpirit_Dir::BS_RB:
		{
			AnimationName += "_RB";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case BoneSpirit_Dir::BS_B:
		{
			AnimationName += "_B";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case BoneSpirit_Dir::BS_L:
		{
			AnimationName += "_L";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case BoneSpirit_Dir::BS_T:
		{
			AnimationName += "_T";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
		case BoneSpirit_Dir::BS_R:
		{
			AnimationName += "_R";
			Renderer_->SetChangeAnimation(AnimationName);
			break;
		}
	}
}

bool BoneSpirit::MonsterDetect()
{
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());
	for (int y = -10; y <= 10; ++y)
	{
		for (int x = -10; x <= 10; ++x)
		{
			TileIndex CheckTileIndex = CurTileIndex + TileIndex(x, y);
			TargetMonster_ = GlobalValue::CatacombsMap->MonsterTileIndexCheck(CheckTileIndex);
			if (nullptr != TargetMonster_)
			{
				return true;
			}
		}
	}

	return false;
}

// 클릭지점까지 이동상태
void BoneSpirit::StartMoveState()
{
	TargetDirCheckAndAnimationSetting(MouseClickPos_, "Move");

	// 마우스를 클릭한 지점에 몬스터가 존재하지않다면 마우스 클릭지점가지 네비게이션 생성
	if (false == Targeting_)
	{
		MovePath_.clear();
		float4 TargetPos = MouseClickPos_ - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Player_ProjectileSkill, NavigationIndex_, GetTransform()->GetWorldPosition(), TargetPos);
		if (false == MovePath_.empty())
		{
			// 다음 이동타일인덱스 Get
			MoveTargetTile_.Index_ = MovePath_.front().Index_;

			// 타겟위치로 지정된 경로의 인덱스제거
			MovePath_.pop_front();

			// 현재 플레이어가 존재하는 타일과 타겟위치 타일인덱스의 방향을 알아내어 
			// 플레이어의 이동방향을 설정한다.
			float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
			MoveTargetDir_ = DirPos.NormalizeReturn3D();
		}
	}
}

void BoneSpirit::UpdateMoveState()
{
	// 타겟지정을 해서 발사했을경우
	if (true == Targeting_)
	{
		// 타겟방향으로 발사
		State_.ChangeState("Fire");
		return;
	}
	// 타겟지정없이 발사했을경우
	else
	{
		if (MoveTargetTile_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()))
		{
			// 마우스 클릭지점까지 이동후 타겟몬스터 탐색
			if (false == MovePath_.empty())
			{
				// 타겟타일 인덱스 변경
				MoveTargetTile_.Index_ = MovePath_.front().Index_;

				// 현재 목표타일까지의 방향을 계산 후
				float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
				MoveTargetDir_ = DirPos.NormalizeReturn3D();

				// 현재 이동방향 및 애니메이션 변경하고,
				float4 MovePos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_);
				TargetDirCheckAndAnimationSetting(MovePos, "Move");

				// 타겟위치로 지정된 경로의 인덱스제거
				MovePath_.pop_front();
			}
			else
			{
				// 탐색하여 몬스터를 찾았다면 타겟방향으로 발사
				State_.ChangeState("Search");
				return;
			}
		}

		GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);
	}
}

void BoneSpirit::EndMoveState()
{
	MoveTargetDir_ = float4::ZERO;
}

// 타겟탐색 상태
void BoneSpirit::StartSearchState()
{
	// 일정범위 타겟 찾기
	if (true == MonsterDetect())
	{
		Targeting_ = true;

		// 타겟위치 이동경로 생성
		MovePath_.clear();
		float4 CurTargetPos = TargetMonster_->GetTransform()->GetWorldPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Player_ProjectileSkill, NavigationIndex_, GetTransform()->GetWorldPosition(), CurTargetPos);
		if (false == MovePath_.empty())
		{
			// 다음 이동타일인덱스 Get
			MoveTargetTile_.Index_ = MovePath_.front().Index_;

			// 타겟위치로 지정된 경로의 인덱스제거
			MovePath_.pop_front();

			// 현재 플레이어가 존재하는 타일과 타겟위치 타일인덱스의 방향을 알아내어 
			// 플레이어의 이동방향을 설정한다.
			float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
			MoveTargetDir_ = DirPos.NormalizeReturn3D();
		}
	}
	else
	{
		// 논타겟팅 발사에서 근처 몬스터 탐색에도 실패했다면 바로 사망
		Death();
	}
}

void BoneSpirit::UpdateSearchState()
{
	// 이동 처리
	if (nullptr != TargetMonster_ && true == Targeting_) // 타겟이 존재하면 네비게이션 발동
	{
		if (MoveTargetTile_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()))
		{
			if (false == MovePath_.empty())
			{
				// 타겟타일 인덱스 변경
				MoveTargetTile_.Index_ = MovePath_.front().Index_;

				// 현재 목표타일까지의 방향을 계산 후
				float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
				MoveTargetDir_ = DirPos.NormalizeReturn3D();

				// 현재 이동방향 및 애니메이션 변경하고,
				float4 MovePos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_);
				TargetDirCheckAndAnimationSetting(MovePos, "Move");

				// 타겟위치로 지정된 경로의 인덱스제거
				MovePath_.pop_front();
			}
			else
			{
				Death();
			}
		}

		GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);
	}
}

void BoneSpirit::EndSearchState()
{
	MoveTargetDir_ = float4::ZERO;
}

// 발사 상태
void BoneSpirit::StartFireState()
{
	TargetDirCheckAndAnimationSetting(TargetMonster_->GetTransform()->GetWorldPosition(), "Move");

	// 이동방향 셋팅
	float4 DirPos = TargetMonster_->GetTransform()->GetWorldPosition() - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
	MoveTargetDir_ = DirPos.NormalizeReturn3D();
}

void BoneSpirit::UpdateFireState()
{
	GetTransform()->SetWorldDeltaTimeMove(MoveTargetDir_ * MoveSpeed_);
}

void BoneSpirit::EndFireState()
{
	MoveTargetDir_ = float4::ZERO;
}

// 폭발상태
void BoneSpirit::StartExplodeState()
{
	// 폭발애니메이션으로 변경
	AnimationChangeCheck("Explode");

	// 발사 종료
	FireStart_ = false;
}

void BoneSpirit::UpdateExplodeState()
{
}

void BoneSpirit::EndExplodeState()
{
}

void BoneSpirit::ExplodeAnimationEnd()
{
	// 충돌 후 폭발애니메이션 프레임 종료시 호출되며,
	// 사망 처리 한다.
	Death();
}

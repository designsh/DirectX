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
	if (Angle < 0.0f) // ������
	{
		if (Angle > -60.f && Angle <= -30.f)
		{
			// ����
			CurDir_ = BoneSpirit_Dir::BS_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDir_ = BoneSpirit_Dir::BS_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDir_ = BoneSpirit_Dir::BS_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDir_ = BoneSpirit_Dir::BS_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDir_ = BoneSpirit_Dir::BS_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDir_ = BoneSpirit_Dir::BS_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDir_ = BoneSpirit_Dir::BS_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDir_ = BoneSpirit_Dir::BS_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDir_ = BoneSpirit_Dir::BS_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDir_ = BoneSpirit_Dir::BS_B;
		}
	}

	// �ִϸ��̼� ����
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

// Ŭ���������� �̵�����
void BoneSpirit::StartMoveState()
{
	TargetDirCheckAndAnimationSetting(MouseClickPos_, "Move");

	// ���콺�� Ŭ���� ������ ���Ͱ� ���������ʴٸ� ���콺 Ŭ���������� �׺���̼� ����
	if (false == Targeting_)
	{
		MovePath_.clear();
		float4 TargetPos = MouseClickPos_ - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Player_ProjectileSkill, NavigationIndex_, GetTransform()->GetWorldPosition(), TargetPos);
		if (false == MovePath_.empty())
		{
			// ���� �̵�Ÿ���ε��� Get
			MoveTargetTile_.Index_ = MovePath_.front().Index_;

			// Ÿ����ġ�� ������ ����� �ε�������
			MovePath_.pop_front();

			// ���� �÷��̾ �����ϴ� Ÿ�ϰ� Ÿ����ġ Ÿ���ε����� ������ �˾Ƴ��� 
			// �÷��̾��� �̵������� �����Ѵ�.
			float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
			MoveTargetDir_ = DirPos.NormalizeReturn3D();
		}
	}
}

void BoneSpirit::UpdateMoveState()
{
	// Ÿ�������� �ؼ� �߻��������
	if (true == Targeting_)
	{
		// Ÿ�ٹ������� �߻�
		State_.ChangeState("Fire");
		return;
	}
	// Ÿ���������� �߻��������
	else
	{
		if (MoveTargetTile_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()))
		{
			// ���콺 Ŭ���������� �̵��� Ÿ�ٸ��� Ž��
			if (false == MovePath_.empty())
			{
				// Ÿ��Ÿ�� �ε��� ����
				MoveTargetTile_.Index_ = MovePath_.front().Index_;

				// ���� ��ǥŸ�ϱ����� ������ ��� ��
				float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
				MoveTargetDir_ = DirPos.NormalizeReturn3D();

				// ���� �̵����� �� �ִϸ��̼� �����ϰ�,
				float4 MovePos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_);
				TargetDirCheckAndAnimationSetting(MovePos, "Move");

				// Ÿ����ġ�� ������ ����� �ε�������
				MovePath_.pop_front();
			}
			else
			{
				// Ž���Ͽ� ���͸� ã�Ҵٸ� Ÿ�ٹ������� �߻�
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

// Ÿ��Ž�� ����
void BoneSpirit::StartSearchState()
{
	// �������� Ÿ�� ã��
	if (true == MonsterDetect())
	{
		Targeting_ = true;

		// Ÿ����ġ �̵���� ����
		MovePath_.clear();
		float4 CurTargetPos = TargetMonster_->GetTransform()->GetWorldPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		MovePath_ = GlobalValue::CatacombsMap->NavgationFind8Way(NavigationObjectType::Player_ProjectileSkill, NavigationIndex_, GetTransform()->GetWorldPosition(), CurTargetPos);
		if (false == MovePath_.empty())
		{
			// ���� �̵�Ÿ���ε��� Get
			MoveTargetTile_.Index_ = MovePath_.front().Index_;

			// Ÿ����ġ�� ������ ����� �ε�������
			MovePath_.pop_front();

			// ���� �÷��̾ �����ϴ� Ÿ�ϰ� Ÿ����ġ Ÿ���ε����� ������ �˾Ƴ��� 
			// �÷��̾��� �̵������� �����Ѵ�.
			float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
			MoveTargetDir_ = DirPos.NormalizeReturn3D();
		}
	}
	else
	{
		// ��Ÿ���� �߻翡�� ��ó ���� Ž������ �����ߴٸ� �ٷ� ���
		Death();
	}
}

void BoneSpirit::UpdateSearchState()
{
	// �̵� ó��
	if (nullptr != TargetMonster_ && true == Targeting_) // Ÿ���� �����ϸ� �׺���̼� �ߵ�
	{
		if (MoveTargetTile_ == GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition()))
		{
			if (false == MovePath_.empty())
			{
				// Ÿ��Ÿ�� �ε��� ����
				MoveTargetTile_.Index_ = MovePath_.front().Index_;

				// ���� ��ǥŸ�ϱ����� ������ ��� ��
				float4 DirPos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_) - float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y);
				MoveTargetDir_ = DirPos.NormalizeReturn3D();

				// ���� �̵����� �� �ִϸ��̼� �����ϰ�,
				float4 MovePos = GlobalValue::CatacombsMap->GetWallTileIndexToPos(MoveTargetTile_);
				TargetDirCheckAndAnimationSetting(MovePos, "Move");

				// Ÿ����ġ�� ������ ����� �ε�������
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

// �߻� ����
void BoneSpirit::StartFireState()
{
	TargetDirCheckAndAnimationSetting(TargetMonster_->GetTransform()->GetWorldPosition(), "Move");

	// �̵����� ����
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

// ���߻���
void BoneSpirit::StartExplodeState()
{
	// ���߾ִϸ��̼����� ����
	AnimationChangeCheck("Explode");

	// �߻� ����
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
	// �浹 �� ���߾ִϸ��̼� ������ ����� ȣ��Ǹ�,
	// ��� ó�� �Ѵ�.
	Death();
}

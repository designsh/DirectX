#include "PreCompile.h"
#include "SketelonWarrior.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "CatacombsMap.h"

// ���� �ε���
int SketelonWarrior::WarriorCnt = 0;

SketelonWarrior::SketelonWarrior() :
	WarriorRenderer_(nullptr),
	BodyCollider_(nullptr),
	DetectMonster_(nullptr),
	SketelonWarriorInfo_{},
	State_(),
	PrevState_(SketelonWarriorState::SPAWN),
	CurState_(SketelonWarriorState::SPAWN),
	SpawnPos_(float4::ZERO),
	WarriorNavigationIndex_(-1),
	CheckTime_(1.f),
	CurHP_(100),
	MoveTargetTile_(),
	TargetPos_(float4::ZERO),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(100.f),
	PrevDir_(SketelonWarrior_TargetDir::SW_B),
	CurDir_(SketelonWarrior_TargetDir::SW_B)
{
	WarriorNavigationIndex_ = WarriorCnt;
	++WarriorCnt;
}

SketelonWarrior::~SketelonWarrior()
{
}

void SketelonWarrior::Start()
{
}

void SketelonWarrior::Update(float _DeltaTime)
{
	// ���¾�����Ʈ
	State_.Update();

	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 50.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));
}

void SketelonWarrior::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// Ÿ��Ʋ ȭ�� or �ε�ȭ�� or ĳ���ͻ���ȭ�� or ĳ���ͼ���ȭ�� or ����ȭ�� �̵��� �����̵�����
	if (std::string::npos != _NextLevel->GetName().find("TitleLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("CreateCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("SelectCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("LoadingLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("MapEditorLevel"))
	{
		return;
	}


}

void SketelonWarrior::CurSkeletonDeath()
{
	// �ش� �����ڷ��� ������·� ��ȯ
	State_.ChangeState("Death");
}

void SketelonWarrior::SpawnSketelonWarrior(const float4& _SpawnPos)
{
	SpawnPos_ = _SpawnPos + GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();

	// ���� �̵����� ����
	// => �÷��̾� �ֺ� 10x10 Ÿ���� ������ ������
	if (nullptr != GlobalValue::CurPlayer && nullptr != GlobalValue::CatacombsMap)
	{
		SetMoveRange();
	}

	// �ִϸ��̼� ����
	CreateAnimation();

	// Ư�� �ִϸ��̼� ����� ȣ��Ǵ� �Լ� ���
	CreateAnimationEndCallbackFunction();

	// FSM State ����
	CreateFSMState();

	// ��ȯ �ִϸ��̼� ����
	ChangeAnimationCheck("Spawn");

	// ��ų���� = ��ȯ������
	MainPlayerInfomation::GetInst().GetSkillInfo(70, SketelonWarriorInfo_);

	// �׺���̼� ����
	GlobalValue::CatacombsMap->CreateNavitaion(NavigationObjectType::Player_SketelonWarrior, WarriorNavigationIndex_);
}

void SketelonWarrior::SetMoveRange()
{
	// �÷��̾ ���� ��ġ�� Ÿ�� �������� ���� ��ȯ�� ��ȯ���� �̵������� �����Ѵ�.
	TileIndex PlayerTile = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());

	// ���� �̵����ѹ��� Ŭ���� ��
	MaxMoveRange_.clear();

	// �ű� �̵����ѹ��� ����
	for (int y = -5; y <= 5; ++y)
	{
		for (int x = -5; x <= 5; ++x)
		{
			MaxMoveRange_.push_back(PlayerTile + TileIndex(x, y));
		}
	}
}

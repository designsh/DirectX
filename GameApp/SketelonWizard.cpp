#include "PreCompile.h"
#include "SketelonWizard.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"

#include "CatacombsMap.h"

int SketelonWizard::WizardCnt = 0;

SketelonWizard::SketelonWizard() :
	WizardRenderer_(nullptr),
	BodyCollider_(nullptr),
	DetectMonster_(nullptr),
	SketelonWizardInfo_{},
	State_(),
	PrevState_(SketelonWizardState::SPAWN),
	CurState_(SketelonWizardState::SPAWN),
	SpawnPos_(float4::ZERO),
	WizardNavigationIndex_(-1),
	WizardType_(SkeletonWizardType::NONE),
	CheckTime_(1.f),
	CurHP_(100),
	MoveTargetTile_(),
	TargetPos_(float4::ZERO),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(100.f),
	PrevDir_(SketelonWizard_TargetDir::SW_B),
	CurDir_(SketelonWizard_TargetDir::SW_B)
{
	WizardNavigationIndex_ = WizardCnt;
	++WizardCnt;
}

SketelonWizard::~SketelonWizard()
{
}

void SketelonWizard::Start()
{
}

void SketelonWizard::Update(float _DeltaTime)
{
	// 상태업데이트
	State_.Update();

	// Z Order 갱신
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 50.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 20.f);
}

void SketelonWizard::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 타이틀 화면 or 로딩화면 or 캐릭터생성화면 or 캐릭터선택화면 or 엔딩화면 이동시 액터이동없음
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

void SketelonWizard::CurSkeletonDeath()
{
	// 해당 스켈텔론을 사망상태로 전환
	State_.ChangeState("Death");
}

void SketelonWizard::SpawnSketelonWizard(SkeletonWizardType _WizardType, const float4& _SpawnPos)
{
	// 기본 정보 저장
	WizardType_ = _WizardType;
	SpawnPos_ = _SpawnPos + GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();

	// 최초 이동범위 셋팅
	// => 플레이어 주변 10x10 타일의 범위를 가진다
	if (nullptr != GlobalValue::CurPlayer && nullptr != GlobalValue::CatacombsMap)
	{
		SetMoveRange();
	}

	// 애니메이션 생성
	CreateAnimation();

	// 특정 애니메이션 종료시 호출되는 함수 등록
	CreateAnimationEndCallbackFunction();

	// FSM State 생성
	CreateFSMState();

	// 소환 애니메이션 실행
	ChangeAnimationCheck("Spawn");

	// 스킬정보 = 소환수정보
	MainPlayerInfomation::GetInst().GetSkillInfo(80, SketelonWizardInfo_);

	// 네비게이션 생성
	GlobalValue::CatacombsMap->CreateNavitaion(NavigationObjectType::Player_SketelonWizard, WizardNavigationIndex_);
}

void SketelonWizard::SetMoveRange()
{
	// 플레이어가 현재 위치한 타일 기준으로 현재 소환된 소환수의 이동범위를 설정한다.
	TileIndex PlayerTile = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());

	// 기존 이동제한범위 클리어 후
	MaxMoveRange_.clear();

	// 신규 이동제한범위 생성
	for (int y = -5; y <= 5; ++y)
	{
		for (int x = -5; x <= 5; ++x)
		{
			MaxMoveRange_.push_back(PlayerTile + TileIndex(x, y));
		}
	}
}

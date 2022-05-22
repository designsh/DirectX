#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineLevel.h>

#include "MainPlayerInfomation.h"
#include "MouseObject.h"

// 플레이어 전용 UI 관련
#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_Stamina.h"
#include "MainPlayer_CurExpProgressBar.h"
#include "MainPlayer_CurrentHP.h"
#include "MainPlayer_CurrentMP.h"
#include "StatView.h"
#include "SkillView.h"
#include "InventoryView.h"
#include "GameEndMenuView.h"

// 공통
#include "GlobalEnumClass.h"
#include "GlobalValue.h"

// 전체 UI 관련
#include "SummonsEmblem.h"

// 맵 관련
#include "TownMap.h"
#include "CatacombsMap.h"

// NPC 관련
#include "WeaponNPC.h"
#include "ChandleryNPC.h"
#include "NPC_TopMenuBar.h"
#include "NPC_BuySellView.h"

// 오브젝트 관련
#include "Portal.h"
#include "Storehouse.h"
#include "StoreView.h"

// 소환수관련
#include "SummonsGolem.h"
#include "SketelonWarrior.h"
#include "SketelonWizard.h"

// 스킬관련
#include "BoneSpirit.h"

int MainPlayer::ArrangeRoomNo_ = -1;
int MainPlayer::CurLeftSkill_ = 0;
int MainPlayer::CurRightSkill_ = 0;

MainPlayer::MainPlayer() :
	IsTown_(true),
	IsRun_(false),
	IsInventoryView_(false),
	IsStateView_(false),
	IsSkillView_(false),
	IsRightSkillList_(false),
	IsLeftSkillList_(false),
	IsStorehouse_(false),
	IsGameEndMenu_(false),
	IsMove_(false),
	IsDefaultZOrderChangeChk_(false),
	IsFrameZOrderChangeChk_(false),
	SkillCastPos_(float4::ZERO),
	SummonsGolem_(nullptr),
	DeathMonster_(nullptr),
	TargetMonster_(nullptr),
	CurHP_(100),
	CurMP_(100),
	PrevEXP_(0),
	CurEXP_(0),
	PrevLevel_(1),
	CurLevel_(1),
	HaveGold_(0),
	State_(),
	BodyCollider_(nullptr),
	RenderSize_(float4(256.f, 256.f)),
	PrevMoveTargetPos_(float4::ZERO),
	CurMoveTargetPos_(float4::ZERO),
	PrevDirect_(TargetDirect::DIR_B),
	CurDirect_(TargetDirect::DIR_B),
	PrevState_(PlayerState::STAT_TN),
	CurState_(PlayerState::STAT_TN),
	BottomStateBar_(nullptr),
	StatView_(nullptr),
	SkillView_(nullptr),
	InventoryView_(nullptr),
	GameEndMenuView_(nullptr),
	MoveSpeed_(200.f),
	MoveTargetDir_(float4::ZERO),
	MoveTargetIndex_(TileIndex())
{
	IsItemEquipState_.clear();
	for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
	{
		IsItemEquipState_.insert(std::map<RendererPartType, bool>::value_type(static_cast<RendererPartType>(i), false));
	}
}

MainPlayer::~MainPlayer()
{
	if (!PartRenderer_.empty())
	{
		PartRenderer_.clear();
	}

	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		DirectRenderOrder_[i].clear();
	}
}

void MainPlayer::Start()
{
	// 플레이어 초기화
	MainPlayerinitialization();

	// 하단 상태바
	BottomStateBar_ = GetLevel()->CreateActor<BottomStateBar>();

	// 스킬창
	SkillView_ = GetLevel()->CreateActor<SkillView>();

	// 스탯창
	StatView_ = GetLevel()->CreateActor<StatView>();

	// 인벤토리창
	InventoryView_ = GetLevel()->CreateActor<InventoryView>();

	// 게임종료메뉴 창
	GameEndMenuView_ = GetLevel()->CreateActor<GameEndMenuView>();

	// ================================== 키생성 ================================== //
	// 스킬창 열기
	if (false == GameEngineInput::GetInst().IsKey("SkillViewActive"))
	{
		GameEngineInput::GetInst().CreateKey("SkillViewActive", 'T');
	}

	// 스탯창 열기
	if (false == GameEngineInput::GetInst().IsKey("StatViewActive"))
	{
		GameEngineInput::GetInst().CreateKey("StatViewActive", 'A');
	}

	// 인벤토리 열기
	if (false == GameEngineInput::GetInst().IsKey("InventoryActive"))
	{
		GameEngineInput::GetInst().CreateKey("InventoryActive", 'I');
	}

	// 게임종료메뉴 열기
	if (false == GameEngineInput::GetInst().IsKey("GameEndMenuActive"))
	{
		GameEngineInput::GetInst().CreateKey("GameEndMenuActive", VK_ESCAPE);
	}

	// 스태미나 활성/비활성
	if (false == GameEngineInput::GetInst().IsKey("StaminaActive"))
	{
		GameEngineInput::GetInst().CreateKey("StaminaActive", 'R');
	}

	// ============================================ 테스트용 ============================================ //
	if (false == GameEngineInput::GetInst().IsKey("TESTLEVELUP"))
	{
		GameEngineInput::GetInst().CreateKey("TESTLEVELUP", 'P');
	}
	if (false == GameEngineInput::GetInst().IsKey("TESTDAMAGE"))
	{
		GameEngineInput::GetInst().CreateKey("TESTDAMAGE", 'O');
	}
}

void MainPlayer::Update(float _DeltaTime)
{
	// 현재 마우스 위치가 화면을 벗어나면 키입력 불가
	if (true == GameEngineWindow::GetInst().IsWindowRangeOut(GameEngineInput::GetInst().GetMousePos()))
	{
		return;
	}

	// 현재 프리카메라모드이면 입력처리 불가
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	// 플레이어 UI활성화관련 키체크
	PlayerUIActiveKeyCheck();

	// 플레이어 이동관련 키체크
	PlayerMoveKeyCheck();

	// 플레이어 스킬관련 키체크
	PlayerSkillCastKeyCheck();

	// 상태별 행동패턴 처리
	State_.Update();

#pragma region 테스트키
	if (true == GameEngineInput::GetInst().Down("TESTLEVELUP"))
	{
		// 테스트 경험치 증가
		int TestEXP = 10;
		BottomStateBar_->GetEXPProgressBarControl()->AddEXP(TestEXP);
	}

	if (true == GameEngineInput::GetInst().Down("TESTDAMAGE"))
	{
		// 테스트용 데미지
		DelCurrentHP(10);
		DelCurrentMP(10);
	}
#pragma endregion

#pragma region 플레이어충돌체
	if (nullptr != BodyCollider_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		// 충돌체 위치 갱신
		float4 MyPos = GetTransform()->GetLocalPosition();
		float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
		MyPos.z = 0.f;
		CamPos.z = 0.f;
		BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Object), std::bind(&MainPlayer::PlayerBodyCollision, this, std::placeholders::_1));
	}
#pragma endregion

#pragma region 좌표상의 Y값 정렬
	if (false == IsTown_)
	{
		float4 CurPlayerPos = GetTransform()->GetWorldPosition();
		TileIndex CurPlayerTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(CurPlayerPos.x, CurPlayerPos.y - 53.f));
		GetTransform()->SetLocalZOrder(-static_cast<float>(CurPlayerTileIndex.X_ + CurPlayerTileIndex.Y_) + 20.f);
	}
#pragma endregion

	// 카메라는 플레이어를 따라 다닌다.
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y));
}

void MainPlayer::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
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

	// 하단상태바
	if (nullptr != BottomStateBar_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, BottomStateBar_);
	}

	// 상태창
	if (nullptr != StatView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, StatView_);
	}

	// 스킬창
	if (nullptr != SkillView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, SkillView_);
	}

	// 인벤토리창
	if (nullptr != InventoryView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, InventoryView_);
	}

	// 게임종료메뉴
	if (nullptr != GameEndMenuView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, GameEndMenuView_);
	}

	// 메인플레이어
	if (std::string::npos != _NextLevel->GetName().find("TownLevel"))
	{
		// 기존 이동경로 초기화 및 이동 Flag 해제
		MovePath_.clear();
		IsMove_ = false;
		ChangeFSMState("Natural_Town");

		GetLevel()->SetLevelActorMove(_NextLevel, this);
		_NextLevel->GetMainCameraActor()->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(0.0f, 0.0f, -100.0f));
	}
	else if (std::string::npos != _NextLevel->GetName().find("CatacombsLevel"))
	{
		// 기존 이동경로 초기화
		MovePath_.clear();
		IsMove_ = false;
		ChangeFSMState("Natural_Field");

		GetTransform()->SetLocalZOrder(-53.f);
		GetLevel()->SetLevelActorMove(_NextLevel, this);
		_NextLevel->GetMainCameraActor()->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(0.0f, 0.0f, -300.0f));
	}
}

void MainPlayer::TownMapObjectCheck(const float4& _MousePos)
{
	// 마을맵에 존재하는 모든 오브젝트 상호작용 활성화해제 체크

	// 포탈
	if (nullptr != GlobalValue::Portal)
	{
		// 활성화되어있다면 해제
		if (true == GlobalValue::Portal->GetPortalInteractionFlag())
		{
			// 단, 마우스가 클릭한지점이 포탈이 존재하는 타일이 아닌경우에만 해제
			GlobalValue::Portal->PortMoveableFlagOff(_MousePos);
		}
	}

	// 창고는 제외
}

void MainPlayer::RandomMapObjectCheck(const float4& _MousePos)
{
	// 필드맵에 존재하는 모든 오브젝트 상호작용 활성화해제 체크

	// 아이템상자

	// HP우물

	// MP우물

	// 스태미나우물

	// 포탈
	if (nullptr != GlobalValue::Portal)
	{
		// 활성화되어있다면 해제
		if (true == GlobalValue::Portal->GetPortalInteractionFlag())
		{
			// 단, 마우스가 클릭한지점이 포탈이 존재하는 타일이 아닌경우에만 해제
			GlobalValue::Portal->PortMoveableFlagOff(_MousePos);
		}
	}
}

void MainPlayer::PlayerUIActiveKeyCheck()
{
	// 스킬창 열기
	if (true == GameEngineInput::GetInst().Down("SkillViewActive"))
	{
		if (false == PlayerUIActiveConditionCheck())
		{
			BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(2);
		}
	}
	
	// 스탯창 열기
	if (true == GameEngineInput::GetInst().Down("StatViewActive"))
	{
		if (false == PlayerUIActiveConditionCheck())
		{
			BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(0);
		}
	}

	// 인벤토리 열기
	if (true == GameEngineInput::GetInst().Down("InventoryActive"))
	{
		if (false == PlayerUIActiveConditionCheck())
		{
			BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(1);
		}
	}

	// 게임종료메뉴 열기(임시보류)
	if (true == GameEngineInput::GetInst().Down("GameEndMenuActive"))
	{
		if (false == PlayerUIActiveConditionCheck())
		{
			BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(3);
		}
	}
}

bool MainPlayer::PlayerUIActiveConditionCheck()
{
	// 플레이어의 각 UI관련 활성화/비활성화 처리에 필요한 조건체크

	// NPC의 판매창이 활성화 되어있거나 창고창이 활성화 되어있다면
	// 키입력을 무시한다.(단, 이 조건은 플레이어가 TownLevel에 존재할때만 체크)
	if (true == IsTown_)
	{
		// 무기상인과의 상호작용으로 인한 판매창 활성화 상태
		if (nullptr != GlobalValue::WeaponNPC && true == GlobalValue::WeaponNPC->GetWeaponShop()->IsUpdate())
		{
			return true;
		}
		// 잡화상인과의 상호작용으로 인한 판매창 활성화 상태
		else if (nullptr != GlobalValue::ChandleryNPC && true == GlobalValue::ChandleryNPC->GetChandleryShop()->IsUpdate())
		{
			return true;
		}
		// 창고와의 상호작용으로 인한 창고창 활서와 상태
		else if (nullptr != GlobalValue::Storehouse && true == GlobalValue::Storehouse->GetStoreView()->IsUpdate())
		{
			return true;
		}
	}
	else
	{
		// 필드맵에서 체크를 해야되나???

	}

	return false;
}

void MainPlayer::PlayerMoveKeyCheck()
{
	// 스태미나 활성/비활성
	if (true == GameEngineInput::GetInst().Down("StaminaActive"))
	{
		// 이미 활성화 되어있다면 비활성화
		if (true == IsRun_)
		{
			IsRun_ = false;

			// 하단상태바의 스태미나 활성/비활성버튼 셋팅
			BottomStateBar_->GetStaminaControl()->SetStaminaActive(IsRun_);

			// 플레이어가 이동중이라면 상태전환
			if (true == IsMove_)
			{
				// 마을인지 아닌지 판단
				if (true == IsTown_)
				{
					ChangeFSMState("Walk_Town");
				}
				else
				{
					ChangeFSMState("Walk_Field");
				}
			}
		}
		else // 아니라면 활성화
		{
			IsRun_ = true;

			// 하단상태바의 스태미나 활성/비활성버튼 셋팅
			BottomStateBar_->GetStaminaControl()->SetStaminaActive(IsRun_);

			// 플레이어가 이동중이라면 상태전환
			if (true == IsMove_)
			{
				ChangeFSMState("Run");
			}
		}
	}

	// 마우스 왼쪽버튼
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
#pragma region 게임화면을 벗어나면 이동불가 판단
		if (GameEngineWindow::GetInst().IsWindowRangeOut(GameEngineInput::GetInst().GetMousePos()))
		{
			return;
		}
#pragma endregion

#pragma region 마우스가 이미 UI와 충돌중이라면 이동불가 판단

#pragma region 플레이어 UI
		// 하단상태바와 충돌중이라면 클릭지점 이동불가
		if (true == GlobalValue::CurMouse->GetBottomStateBarCollision())
		{
			return;
		}

		// 스킬트리창 or 인벤토리창과 충돌중이라면 클릭지점 이동불가
		// 단, 클릭지점이 화면의 왼쪽지점이라면 이동가능판단
		if (true == GlobalValue::CurMouse->GetScreenRightUIViewCollision())
		{
			return;
		}

		// 스탯창 or NPC의 판매창 충돌중이라면 클릭지점 이동불가
		// 단, 클릭지점이 화면의 오른쪽지점이라면 이동가능판단
		if (true == GlobalValue::CurMouse->GetScreenLeftUIViewCollision())
		{
			return;
		}

		// 왼쪽스킬목록리스트와 충돌중이라면 이동불가
		if (true == GlobalValue::CurMouse->GetLWeaponSkillListCollision())
		{
			return;
		}

		// 오른쪽스킬목록리스트와 충돌중이라면 이동불가
		if (true == GlobalValue::CurMouse->GetRWeaponSkillListCollision())
		{
			return;
		}

		// 현재 활성화된 팝업과 충돌중이라면 이동불가
		if (true == GlobalValue::CurMouse->GetUIPopupCollision())
		{
			return;
		}
#pragma endregion

#pragma region NPC UI
		if (true == IsTown_) // 마을레벨에만 NPC 존재
		{
			// 상단메뉴바
			if (true == GlobalValue::CurMouse->GetTopMenuBarCollision())
			{
				return;
			}

			// 판매창
			if (true == GlobalValue::CurMouse->GetBuySellViewCollision())
			{
				return;
			}
		}
#pragma endregion

#pragma region 마우스아이템들고있는지판단
		if (true == GlobalValue::CurMouse->IsItemHold())
		{
			// 아이템을 들고있다면 아이템 배치 or 드랍 이전에 이동불가처리
			return;
		}
#pragma endregion

#pragma endregion

		// 이동인지 체크후 이동이라면 방향계산후 상태 변경
		MouseObject* MainMouse = GlobalValue::CurMouse;
		if (nullptr == MainMouse)
		{
			GameEngineDebug::MsgBoxError("현재 마우스 오브젝트를 찾지 못하였습니다!!!!");
			return;
		}

		float4 MousePos = MainMouse->GetTransform()->GetWorldPosition();

#pragma region 오브젝트활성화여부체크
		if (true == IsTown_)
		{
			TownMapObjectCheck(MousePos);
		}
		else
		{
			RandomMapObjectCheck(MousePos);
		}
#pragma endregion

		// 이미 이동중이였다면 현재 경로를 삭제하고 Flag해제 후 플레이어 대기상태 돌입
		if (true == IsMove_)
		{
			MovePath_.clear();
			IsMove_ = false;

			if (true == IsTown_)
			{
				ChangeFSMState("Natural_Town");
			}
			else
			{
				ChangeFSMState("Natural_Field");
			}
		}

		// 현재 방향 전환
		if (true == MoveDirectCheck(MousePos))
		{
			// 이동 시작
			MoveStart(MousePos);
		}
	}
}

void MainPlayer::PlayerSkillCastKeyCheck()
{
	// 마우스 오른쪽버튼
	if (true == GameEngineInput::GetInst().Down("MouseRButton"))
	{
#pragma region 게임화면을 벗어나면 스킬사용불가 판단
		if (GameEngineWindow::GetInst().IsWindowRangeOut(GameEngineInput::GetInst().GetMousePos()))
		{
			return;
		}
#pragma endregion

		if (nullptr != GlobalValue::CurMouse)
		{
			// 마을에서 사용 불가
			if (false == IsTown_)
			{
				// 스킬시전 위치 저장
				SkillCastPos_ = GlobalValue::CurMouse->GetTransform()->GetWorldPosition();
				if (true == MoveDirectCheck(SkillCastPos_))
				{
					// 현재 선택된 스킬이 기본공격이아니라면 스킬공격 모션으로 전환
					if (0 != CurRightSkill_)
					{
						// 스켈텔론 소환 스킬일때는 마우스와 몬스터의 시체가 충돌중인지 체크한다.
						if (70 == CurRightSkill_ || 80 == CurRightSkill_)
						{
							// 몬스터와 마우스가 충돌중(몬스터 시체와 충돌중이여야만 가능)
							if (true == GlobalValue::CurMouse->GetMonsterCollision())
							{
								// 사용하려는 시체의 몬스터를 가지고있는다.
								DeathMonster_ = GlobalValue::CurMouse->GetCurCollisionMonster();

								// 스킬공격 모션 종료시 현재 선택된 스킬 시전
								ChangeFSMState("Special_Attack");
							}
							else
							{
								DeathMonster_ = nullptr;
							}
						}
						else if (93 == CurRightSkill_)
						{
							if (true == GlobalValue::CurMouse->GetMonsterCollision())
							{
								// 타겟팅한 본스피릿 발사체
								TargetMonster_ = GlobalValue::CurMouse->GetCurCollisionMonster();
							}
							else
							{
								TargetMonster_ = nullptr;
							}

							ChangeFSMState("Special_Attack");
						}
						else
						{
							// 스킬공격 모션 종료시 현재 선택된 스킬 시전
							ChangeFSMState("Special_Attack");
						}
					}
				}
			}
		}
	}
}

void MainPlayer::GolemSummons()
{
	// 스킬별 소환 골렘이 달라짐
	// 단, 어떠한 타입의 골렘이든 한개의 골렘만 가짐
	
	// 현재 소환된 골렘이 존재한다면 해당 골렘을 먼저 죽인다.
	if (nullptr != SummonsGolem_)
	{
		SummonsGolem_->CurGolemDeath();
		SummonsGolem_ = nullptr;
	}

	switch (CurRightSkill_)
	{
		case 75: // ClayGolem 소환
		{
			SummonsGolem_ = GetLevel()->CreateActor<SummonsGolem>();
			SummonsGolem_->SpawnGolem(GolemType::CLAY, SkillCastPos_);

			GlobalValue::Emblem->GolemEmblemUpdate(GolemType::CLAY);
			break;
		}
		case 85: // BloodGolem 소환
		{
			SummonsGolem_ = GetLevel()->CreateActor<SummonsGolem>();
			SummonsGolem_->SpawnGolem(GolemType::BLOOD, SkillCastPos_);

			GlobalValue::Emblem->GolemEmblemUpdate(GolemType::BLOOD);
			break;
		}
		case 90: // IronGolem 소환
		{
			SummonsGolem_ = GetLevel()->CreateActor<SummonsGolem>();
			SummonsGolem_->SpawnGolem(GolemType::IRON, SkillCastPos_);

			GlobalValue::Emblem->GolemEmblemUpdate(GolemType::IRON);
			break;
		}
		case 94: // FireGolem 소환
		{
			SummonsGolem_ = GetLevel()->CreateActor<SummonsGolem>();
			SummonsGolem_->SpawnGolem(GolemType::FIRE, SkillCastPos_);

			GlobalValue::Emblem->GolemEmblemUpdate(GolemType::FIRE);
			break;
		}
	}
}

void MainPlayer::SkeletonWarriorSummons()
{
	// 현재 마우스가 몬스터와 충돌중이고, 해당 몬스터가 시체상태일때 시전 가능 판정

	// 스켈텔론(전사) 소환
	if (CurRightSkill_ == 70)
	{
		// 최대 소환갯수 초과시 가장 첫번째 생성된 스켈텔론(전사형) 사망 처리 후
		if (SummonsWarrior <= static_cast<int>(SummonsSketelonWarrior_.size()))
		{
			// 사망 처리
			SketelonWarrior* DeathSketelon = SummonsSketelonWarrior_.front();
			DeathSketelon->CurSkeletonDeath();

			// 생성 갯수 감소
			SketelonWarrior::WarriorCnt -= 1;
			
			// 목록에서 제거
			SummonsSketelonWarrior_.pop_front();

			// 현재 목록에 존재하는 소환수들의 네비게이션 인덱스를 감소
			for (auto& CurSketelon : SummonsSketelonWarrior_)
			{
				CurSketelon->DecreaseNavationIndex();
			}
		}

		// 해당 스킬에 사용된 몬스터는 실질적으로 사망처리되며, 스켈텔론이 생성된다.
		if (nullptr != DeathMonster_)
		{
			// 현재 마우스가 선택한 몬스터를 사망처리
			DeathMonster_->GetActor()->Death();

			// 맵의 몬스터 목록에서 제거
			GlobalValue::CatacombsMap->MonsterDeathToListDelete(DeathMonster_->GetActor());

			DeathMonster_ = nullptr;

			// 새로운 스켈텔론 생성 후 목록에 추가
			SketelonWarrior* NewSketelon = GetLevel()->CreateActor<SketelonWarrior>();
			NewSketelon->SpawnSketelonWarrior(SkillCastPos_);
			SummonsSketelonWarrior_.push_back(NewSketelon);

			// 엠블럼 업데이트
			GlobalValue::Emblem->SketelonWarriorUpdate(SketelonWarrior::WarriorCnt);
		}
	}
}

void MainPlayer::SkeletonWizardSummons()
{
	// 현재 마우스가 몬스터와 충돌중이고, 해당 몬스터가 시체상태일때 시전 가능 판정

	// 스켈텔론(마법사) 소환
	if (CurRightSkill_ == 80)
	{
		// 최대 소환갯수 초과시 가장 첫번째 생성된 스켈텔론(전사형) 사망 처리 후
		if (SummonsWizard <= static_cast<int>(SummonsSketelonWizard_.size()))
		{
			// 사망 처리
			SketelonWizard* DeathSketelon = SummonsSketelonWizard_.front();
			DeathSketelon->CurSkeletonDeath();

			// 생성 갯수 감소
			SketelonWizard::WizardCnt -= 1;

			// 목록에서 제거
			SummonsSketelonWizard_.pop_front();

			// 현재 목록에 존재하는 소환수들의 네비게이션 인덱스를 감소
			for (auto& CurSketelon : SummonsSketelonWizard_)
			{
				CurSketelon->DecreaseNavationIndex();
			}
		}

		// 해당 스킬에 사용된 몬스터는 실질적으로 사망처리되며, 스켈텔론이 생성된다.
		if (nullptr != DeathMonster_)
		{
			// 현재 마우스가 선택한 몬스터를 사망처리
			DeathMonster_->GetActor()->Death();

			// 맵의 몬스터 목록에서 제거
			GlobalValue::CatacombsMap->MonsterDeathToListDelete(DeathMonster_->GetActor());

			DeathMonster_ = nullptr;

			// 새로운 스켈레톤 생성 후 목록에 추가
			// 단, 생성되는 스켈레톤의 타입은 랜덤하게 지정된다.
			GameEngineRandom TypeRandom;
			SkeletonWizardType RandType = static_cast<SkeletonWizardType>(TypeRandom.RandomInt(0, 3));
			SketelonWizard* NewSketelon = GetLevel()->CreateActor<SketelonWizard>();
			NewSketelon->SpawnSketelonWizard(RandType, SkillCastPos_);
			SummonsSketelonWizard_.push_back(NewSketelon);

			// 엠블럼 업데이트
			GlobalValue::Emblem->SketelonWizardUpdate(SketelonWizard::WizardCnt);
		}
	}
}

void MainPlayer::SkeletonWarriorDeath(SketelonWarrior* _DeathWarrior)
{
	std::list<SketelonWarrior*>::iterator StartIter = SummonsSketelonWarrior_.begin();
	std::list<SketelonWarrior*>::iterator EndIter = SummonsSketelonWarrior_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter) == _DeathWarrior)
		{
			SummonsSketelonWarrior_.erase(StartIter);
			_DeathWarrior->Death();
			return;
		}
	}

	if (nullptr != _DeathWarrior)
	{
		_DeathWarrior->Death();
	}
}

void MainPlayer::SkeletonWizardDeath(SketelonWizard* _DeathWizard)
{
	std::list<SketelonWizard*>::iterator StartIter = SummonsSketelonWizard_.begin();
	std::list<SketelonWizard*>::iterator EndIter = SummonsSketelonWizard_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if ((*StartIter) == _DeathWizard)
		{
			SummonsSketelonWizard_.erase(StartIter);
			_DeathWizard->Death();
			break;
		}
	}
}

SummonsGolem* MainPlayer::SummonsGolemTileCheck(TileIndex _CheckTile)
{
	if (nullptr != GlobalValue::CatacombsMap && nullptr != SummonsGolem_)
	{
		TileIndex CurGolemIndex = GlobalValue::CatacombsMap->GetWallTileIndex(SummonsGolem_->GetTransform()->GetWorldPosition());
		if (CurGolemIndex == _CheckTile)
		{
			return SummonsGolem_;
		}
	}

	return nullptr;
}

SketelonWarrior* MainPlayer::SummonsSkeletonWarriorTileCheck(TileIndex _CheckTile)
{
	if (nullptr != GlobalValue::CatacombsMap)
	{
		for (auto& SketelonWarrior : SummonsSketelonWarrior_)
		{
			if (nullptr != SketelonWarrior)
			{
				TileIndex CurWarriorIndex = GlobalValue::CatacombsMap->GetWallTileIndex(SketelonWarrior->GetTransform()->GetWorldPosition());
				if (CurWarriorIndex == _CheckTile)
				{
					return SketelonWarrior;
				}
			}
		}
	}

	return nullptr;
}

SketelonWizard* MainPlayer::SummonsSkeletonWizardTileCheck(TileIndex _CheckTile)
{
	if (nullptr != GlobalValue::CatacombsMap)
	{
		for (auto& SketelonWizard : SummonsSketelonWizard_)
		{
			if (nullptr != SketelonWizard)
			{
				TileIndex CurWizardIndex = GlobalValue::CatacombsMap->GetWallTileIndex(SketelonWizard->GetTransform()->GetWorldPosition());
				if (CurWizardIndex == _CheckTile)
				{
					return SketelonWizard;
				}
			}
		}
	}

	return nullptr;
}

void MainPlayer::BoneSpiritFire()
{
	if (CurRightSkill_ == 93)
	{
		// 발사체 생성
		BoneSpirit* NewBoneSpirit = GetLevel()->CreateActor<BoneSpirit>();

		// 타겟지정된 발사체
		if (nullptr != TargetMonster_)
		{
			NewBoneSpirit->BoneSpiritFire(GetTransform()->GetWorldPosition(), SkillCastPos_, TargetMonster_->GetActor());
		}
		// 타겟지정이 안된 발사체
		else
		{
			NewBoneSpirit->BoneSpiritFire(GetTransform()->GetWorldPosition(), SkillCastPos_);
		}
	}
}

#include "PreCompile.h"
#include "ChandleryNPC.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "TownMap.h"

#include "MainPlayer.h"
#include "NPC_MessageView.h"
#include "NPC_TopMenuBar.h"
#include "NPC_BuySellView.h"

bool ChandleryNPC::FirstInteraction = false;
bool ChandleryNPC::InteractionFlag = false;

bool ChandleryNPC::GetFirstInteaction()
{
	return FirstInteraction;
}

ChandleryNPC::ChandleryNPC() :
	ChandleryNPCRenderer_(nullptr),
	ChandleryNPCCollision_(nullptr),
	PrevMoveDir_(ChandleryNPC_MoveDir::DIR_L),
	CurMoveDir_(ChandleryNPC_MoveDir::DIR_L),
	PrevState_(ChandleryNPC_FSMState::ST_IDLE),
	CurState_(ChandleryNPC_FSMState::ST_IDLE),
	MoveDelayTime_(5.f),
	MoveSpeed_(100.f),
	MoveStartPos_(float4::ZERO),
	MoveCurPos_(float4::ZERO),
	MoveMinRange_(float4::ZERO),
	MoveMaxRange_(float4::ZERO),
	MessageView_(nullptr),
	TopMenuBar_(nullptr),
	SpeechSound_(nullptr)
{
}

ChandleryNPC::~ChandleryNPC()
{
}

void ChandleryNPC::Start()
{
	// 무기상인관련 생성
	InitChandleryNPC();

	// 무기상인 관련 UI 생성

	// 1. 메세지창(화면중앙상단에 표시)
	MessageView_ = GetLevel()->CreateActor<NPC_MessageView>();
	MessageView_->Off();

	// 2. 상단메뉴(NPC 상단에 표시)
	TopMenuBar_ = GetLevel()->CreateActor<NPC_TopMenuBar>();
	TopMenuBar_->GetTransform()->SetWorldPosition(GetTransform()->GetLocalPosition());
	TopMenuBar_->Off();

	// 음성 사운드 플레이어 생성
	SpeechSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();
}

void ChandleryNPC::Update(float _DeltaTime)
{
	// 상태 갱신
	State_.Update();

	float4 MyPos = GetTransform()->GetLocalPosition();
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	ChandleryNPCCollision_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// 마우스클릭으로 상호작용대기전환시도 On상태일때
	if (true == InteractionFlag)
	{
		InteractionDistanceCheck();
	}

	// 마우스와 충돌체크
	ChandleryNPCCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&ChandleryNPC::MouseLButtonClick, this, std::placeholders::_1));

#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(ChandleryNPCCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

#pragma region 좌표상의 Y값 정렬
	float4 CurPos = GetTransform()->GetWorldPosition();
	TileIndex CurTileIndex = GlobalValue::TownMap->GetPosToTileIndex(float4(CurPos.x, CurPos.y - 53.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));
#pragma endregion
}

NPC_BuySellView* ChandleryNPC::GetChandleryShop()
{
	return TopMenuBar_->GetBuySellView();
}

void ChandleryNPC::MouseLButtonClick(GameEngineCollision* _Other)
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

void ChandleryNPC::InteractionDistanceCheck()
{
	// 이동&대기 상태일때 플레이어와의 거리 체크
	if (CurState_ == ChandleryNPC_FSMState::ST_IDLE || CurState_ == ChandleryNPC_FSMState::ST_WALK)
	{
		// 거리체크
		if (nullptr != GlobalValue::CurPlayer)
		{
			float4 MyPos = GetTransform()->GetLocalPosition();

			// 플레이어를 향한 방향을 알아낸다.
			float4 PlayerPos = GlobalValue::CurPlayer->GetTransform()->GetLocalPosition() - float4(100.f, 100.f);

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
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_RT;
				}
				else if (Angle > -150.f && Angle <= -120.f)
				{
					// 우하단
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_RB;
				}
				else if (Angle > -30.f && Angle <= 0.f)
				{
					// 상단
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_T;
				}
				else if (Angle > -120.f && Angle <= -60.f)
				{
					// 우단
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_R;
				}
				else if (Angle > -180.f && Angle <= -150.f)
				{
					// 하단
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_B;
				}
			}
			else // 왼쪽
			{
				if (Angle > 30.f && Angle <= 60.f)
				{
					// 좌상단
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_LT;
				}
				else if (Angle > 120.f && Angle <= 150.f)
				{
					// 좌하단
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_LB;
				}
				else if (Angle > 0.f && Angle <= 30.f)
				{
					// 상단
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_T;
				}
				else if (Angle > 60.f && Angle <= 120.f)
				{
					// 좌단
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_L;
				}
				else if (Angle > 150.f && Angle <= 180.f)
				{
					// 하단
					CurMoveDir_ = ChandleryNPC_MoveDir::DIR_B;
				}
			}

			// 상호작용대기상태로 상태전환
			State_.ChangeState("ChandleryNPC_CONVERSATION");
		}
	}
}

void ChandleryNPC::SetMoveRange()
{
	// 최초생성 위치 기준으로 해당 NPC의 이동가능범위가 정해진다.
	float4 MyPos = GetTransform()->GetLocalPosition();

	// 최소이동위치
	MoveMinRange_.x = MyPos.x - 150.f;
	MoveMinRange_.y = MyPos.y - 150.f;

	// 최대이동위치
	MoveMaxRange_.x = MyPos.x + 150.f;
	MoveMaxRange_.y = MyPos.y + 150.f;
}

void ChandleryNPC::SetMessageBoxText(const std::string& _Text)
{
	if (nullptr != MessageView_)
	{
		MessageView_->CreateNPCMessageTextList(_Text, NPCClassType::Akara);
	}
}

void ChandleryNPC::SetUIPosition()
{
	TopMenuBar_->GetTransform()->SetWorldPosition(GetTransform()->GetLocalPosition());
}

void ChandleryNPC::SetTopMenu()
{
	TopMenuBar_->CreateNPCTopMenu(NPCClassType::Akara, NPCType::PotionShop);
}

void ChandleryNPC::TopMenuBarInactive()
{
	TopMenuBar_->Off();
	TopMenuBar_->MenuButtonStateReset();
}

void ChandleryNPC::TopMenuBarActive()
{
	TopMenuBar_->On();
	TopMenuBar_->MenuButtonStateReset();
}

void ChandleryNPC::InteractionEnd()
{
	// 외부에서 해당 NPC 상호작용 종료시 호출되며,
	// 상호작용이 종료되었으므로 해당 NPC는 대기상태로 돌입한다.
	State_.ChangeState("ChandleryNPC_IDLE");
}

void ChandleryNPC::SelectConversationMenu()
{
	// 상호작용상태에서 화면에 표시되는 NPC상단메뉴에서 대화메뉴 선택시 호출
	FirstInteraction = false;
	MessageView_->InteractionActive();

	// 자기소개 음성 재생
	SpeechSound_->PlayAlone("Aka_Conversation.wav", 0);

	// 상단메뉴 닫기
	TopMenuBar_->Off();
}

bool ChandleryNPC::SpeechEndCheck()
{
	return SpeechSound_->IsPlay();
}

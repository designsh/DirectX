#include "PreCompile.h"
#include "NPC_MessageView.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

NPC_MessageView::NPC_MessageView() :
	MsgPanel_(nullptr),
	TextMoveSpeed_(20.f),
	SaveMsgText_{},
	CurTextLineIdx_(0),
	MessageLoadStart_(false),
	MessageLoadEnd_(false),
	TextMoveEndPos_(float4::ZERO)
{
}

NPC_MessageView::~NPC_MessageView()
{
}

void NPC_MessageView::Start()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// 메세지 판넬 렌더러 생성
	MsgPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	MsgPanel_->SetImage("MessageView_Panel.png");
	MsgPanel_->SetAlpha(0.5f);
	MsgPanel_->GetTransform()->SetLocalScaling(float4(272.f, 93.f));
	MsgPanel_->GetTransform()->SetLocalPosition(float4(0.f, ScreenHarfSize.y - 50.f));
}

void NPC_MessageView::Update(float _DeltaTime)
{
	// 저장된 메세지 출력시작
	if (true == MessageLoadStart_)
	{
		// CurTextLineIdx_까지의 라인들을 위로 이동시킨다.
		// 단, 목표위치에 도달한 텍스트라인은 초기위치로 재셋팅하고, Off 상태로 전환한다.
		for (int i = 0; i < CurTextLineIdx_; ++i)
		{
			if (true == PrintTextList_[i]->IsUpdate())
			{
				// 위로 이동하므로 y값 비교하여 목표지점을 넘어가면 해당 텍스트라인은 초기셋팅하고 Off
				if (TextMoveEndPos_.y <= PrintTextList_[i]->GetTransform()->GetLocalPosition().y)
				{
					// 초기 위치로 셋팅 후 
					float4 ParentPos = MsgPanel_->GetTransform()->GetLocalPosition();
					PrintTextList_[i]->GetTransform()->SetLocalPosition(float4(ParentPos.x, ParentPos.y - 38.f));

					// Off 상태 전환
					PrintTextList_[i]->Off();

					// 마지막인덱스의 텍스트라인이 표시 및 이동완료시 해당 메세지창 Off 처리
					if (i + 1 == CurTextLineIdx_)
					{
						CurTextLineIdx_ = 0;
						MessageLoadStart_ = false;
						MessageLoadEnd_ = true;
						return;
					}
				}
				else // 아니라면 이동
				{
					float4 CurPos = PrintTextList_[i]->GetTransform()->GetLocalPosition();
					CurPos += (float4::UP * TextMoveSpeed_ * _DeltaTime);
					PrintTextList_[i]->GetTransform()->SetLocalPosition(CurPos);
				}
			}
		}

		// 단, 이전라인과 현재라인의 위치를 비교하여 일정거리가 넘어가면 On
		if (0 < CurTextLineIdx_ && CurTextLineIdx_ < static_cast<int>(PrintTextList_.size()))
		{
			float4 PrevPos = PrintTextList_[CurTextLineIdx_ - 1]->GetTransform()->GetLocalPosition();
			float4 CurPos = PrintTextList_[CurTextLineIdx_]->GetTransform()->GetLocalPosition();
			if (CurPos.y + 10.f <= PrevPos.y)
			{
				// 이전라인들이 모두 이동했다면 현재 라인을 On
				PrintTextList_[CurTextLineIdx_]->On();

				// 현재 라인 인덱스 증가
				++CurTextLineIdx_;
			}
		}

		if(0 == CurTextLineIdx_)
		{
			PrintTextList_[0]->On();

			// 현재 라인 인덱스 증가
			++CurTextLineIdx_;
		}
	}
}

void NPC_MessageView::CreateNPCMessageTextList(const std::string& _Text)
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// 출력되는 메세지 등록
	SaveMsgText_ = _Text;

	// 메세지의 글자수를 이용하여 텍스트목록 생성 갯수 결정(한줄당 최대글자수 30)
	int CurTextTotSize = static_cast<int>(SaveMsgText_.size());
	int TextLineCnt = (CurTextTotSize / 30) %  30;

	// 텍스트 라인 소멸시점 체크
	float4 ParentPos = MsgPanel_->GetTransform()->GetLocalPosition();
	TextMoveEndPos_ = float4(ParentPos.x, ParentPos.y + 38.f);

	// 기존목록제거 후 생성
	int Index = 0;
	PrintTextList_.clear();
	for (int i = 0; i < TextLineCnt + 1; ++i)
	{
		GameEngineUIRenderer* NewTextRenderer = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
		NewTextRenderer->SetImage("MessageView_Panel.png");
		NewTextRenderer->SetAlpha(0.f);
		NewTextRenderer->GetTransform()->SetLocalScaling(float4(272.f, 93.f));
		NewTextRenderer->GetTransform()->SetLocalPosition(float4(ParentPos.x, ParentPos.y - 38.f));

		// 전체문자열에서 특정부분 Text 잘라서 텍스트 셋팅
		std::string PrintText = "";
		int StartIdx = Index * 30;

		int EndIdx = (Index + 1) * 30;
		if (CurTextTotSize <= EndIdx)
		{
			EndIdx = CurTextTotSize;
		}
		PrintText = SaveMsgText_.substr(StartIdx, EndIdx);
		NewTextRenderer->TextSetting("diablo", PrintText, 12.f, FW1_LEFT | FW1_VCENTER, float4::WHITE, float4(-132.f, 0.0f), 35);
		NewTextRenderer->Off();

		PrintTextList_.push_back(NewTextRenderer);

		++Index;
	}
}

void NPC_MessageView::FirstInteractionActive()
{
	// 메세지목록이 존재할때
	if (false == PrintTextList_.empty())
	{
		// NPC 최초 상호작용시 호출되어 메세지 출력
		On();

		// 입력된 메세지 출력 시작 Flag On / 출력 종료 Flag Off
		MessageLoadStart_ = true;
		MessageLoadEnd_ = false;
	}
	else // 텍스트목록이 존재하지않다면
	{
		// 바로 출력 시작 Flag Off / 출력 종료 Flag On
		MessageLoadStart_ = false;
		MessageLoadEnd_ = true;
	}
}

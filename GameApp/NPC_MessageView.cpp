#include "PreCompile.h"
#include "NPC_MessageView.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

NPC_MessageView::NPC_MessageView() :
	MsgPanel_(nullptr),
	SaveMsgText_{},
	CurTextLineIdx_(0),
	MessageLoadStart_(false),
	MessageLoadEnd_(false),
	MessagePrintDelayTime_(0.f),
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
		// 메세지로딩 딜레이타임
		MessagePrintDelayTime_ -= GameEngineTime::GetInst().GetDeltaTime();
		if (0.0f >= MessagePrintDelayTime_)
		{
			// 메세지목록이 존재할때
			if (false == PrintTextList_.empty())
			{
				// 현재 출력해야하는 라인수가 최대치를 넘어가면
				if (static_cast<int>(PrintTextList_.size()) <= CurTextLineIdx_)
				{
					MessagePrintDelayTime_ = 1.f;

					// 해당 메세지 출력종료 Flag On / 출력시작 Flag Off
					MessageLoadStart_ = false;
					MessageLoadEnd_ = true;
				}

				// 아니라면 CurTextLineIdx_ - 1



				// 이전인덱스까지의 텍스트가 모두 On상태이고, 현재인덱스가 On이되면서 
				// 이전인덱스까지의 텍스트들은 목표지점이아니면 상단쪽으로 이동을 하고, 
				// 목표지점에 도달하면 Off 상태로 전환과 동시에 초기위치로 위치를 재셋팅한다.








				// TextEndPosArrive();


			}

			// 딜레이 시간 초기화
			MessagePrintDelayTime_ = 1.f;

			// 현재 라인 인덱스 증가
			++CurTextLineIdx_;
		}
	}
}

void NPC_MessageView::TextEndPosArrive()
{
}

void NPC_MessageView::SetNPCMessage(const std::string& _Text)
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// 출력되는 메세지 등록
	SaveMsgText_ = _Text;

	// 메세지의 글자수를 이용하여 텍스트목록 생성 갯수 결정(한줄당 최대글자수 35)
	int CurTextTotSize = static_cast<int>(SaveMsgText_.size());
	int TextLineCnt = (CurTextTotSize / 35) %  35;

	// 기존목록제거 후 생성
	int Index = 0;
	PrintTextList_.clear();
	for (int i = 0; i < TextLineCnt + 1; ++i)
	{
		GameEngineUIRenderer* NewTextRenderer = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
		NewTextRenderer->SetImage("MessageView_Panel.png");
		NewTextRenderer->SetAlpha(0.f);
		NewTextRenderer->GetTransform()->SetLocalScaling(float4(272.f, 93.f));
		NewTextRenderer->GetTransform()->SetLocalPosition(MsgPanel_->GetTransform()->GetLocalPosition());

		// 전체문자열에서 특정부분 Text 잘라서 텍스트 셋팅
		std::string PrintText = "";
		int StartIdx = Index * 35;

		int EndIdx = (Index + 1) * 35;
		if (CurTextTotSize <= EndIdx)
		{
			EndIdx = CurTextTotSize;
		}
		PrintText = SaveMsgText_.substr(StartIdx, EndIdx);
		NewTextRenderer->TextSetting("diablo", PrintText, 12.f, FW1_LEFT | FW1_VCENTER, float4::WHITE, float4(-132.f, -38.f), 35);
		NewTextRenderer->Off();

		PrintTextList_.push_back(NewTextRenderer);

		++Index;
	}
}

void NPC_MessageView::FirstInteractionActive()
{
	// NPC 최초 상호작용시 호출되어 메세지 출력
	On();

	// 입력된 메세지 출력 시작 Flag On
	MessageLoadStart_ = true;
}

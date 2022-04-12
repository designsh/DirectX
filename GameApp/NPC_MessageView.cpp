#include "PreCompile.h"
#include "NPC_MessageView.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

NPC_MessageView::NPC_MessageView() :
	MsgPanel_(nullptr),
	SaveMsgText_{},
	CurPrintTextIndex_(0),
	MessageLoadStart_(false),
	MessageLoadEnd_(false),
	MessagePrintDelayTime_(0.f)
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
			// 수정중....






			//// 딜레이 시간 초기화
			//MessagePrintDelayTime_ = 1.f;

			//// 저장된 메세지 최대길이 Get
			//int SaveTextLen = static_cast<int>(SaveMsgText_.size());

			//// 현재 출력인덱스를 이용하여 Text 추가하여 출력
			//char CurText = SaveMsgText_[CurPrintTextIndex_];
			//std::string CurString = "";
			//CurString += CurText;
			//MsgPanel_->AddText(CurString);
			//
			//// 현재 출력하는 인덱스와 메세지의 최대길이와 같을때 
			//// 저장된 텍스트 출력 종료
			//if (CurPrintTextIndex_ == SaveTextLen)
			//{
			//	// 종료 Flag On
			//	MessageLoadEnd_ = true;

			//	// 시작가능 Flag Off
			//	MessageLoadStart_ = false;
			//}

			//++CurPrintTextIndex_;
		}
	}
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
	PrintTextList_.clear();
	int Index = 0;
	for (int i = 0; i < TextLineCnt + 1; ++i)
	{
		GameEngineUIRenderer* NewTextRenderer = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
		NewTextRenderer->SetImage("MessageView_Panel.png");
		NewTextRenderer->SetAlpha(0.f);
		NewTextRenderer->GetTransform()->SetLocalScaling(float4(272.f, 93.f));
		NewTextRenderer->GetTransform()->SetLocalPosition(MsgPanel_->GetTransform()->GetLocalPosition());

		// Text 저장
		std::string PrintText = "";


		NewTextRenderer->TextSetting("diablo", PrintText, 12.f, FW1_LEFT | FW1_VCENTER, float4::WHITE, float4(-132.f, -38.f), 35);

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

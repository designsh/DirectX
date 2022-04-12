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

	// �޼��� �ǳ� ������ ����
	MsgPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	MsgPanel_->SetImage("MessageView_Panel.png");
	MsgPanel_->SetAlpha(0.5f);
	MsgPanel_->GetTransform()->SetLocalScaling(float4(272.f, 93.f));
	MsgPanel_->GetTransform()->SetLocalPosition(float4(0.f, ScreenHarfSize.y - 50.f));
}

void NPC_MessageView::Update(float _DeltaTime)
{
	// ����� �޼��� ��½���
	if (true == MessageLoadStart_)
	{
		// �޼����ε� ������Ÿ��
		MessagePrintDelayTime_ -= GameEngineTime::GetInst().GetDeltaTime();
		if (0.0f >= MessagePrintDelayTime_)
		{
			// ������....






			//// ������ �ð� �ʱ�ȭ
			//MessagePrintDelayTime_ = 1.f;

			//// ����� �޼��� �ִ���� Get
			//int SaveTextLen = static_cast<int>(SaveMsgText_.size());

			//// ���� ����ε����� �̿��Ͽ� Text �߰��Ͽ� ���
			//char CurText = SaveMsgText_[CurPrintTextIndex_];
			//std::string CurString = "";
			//CurString += CurText;
			//MsgPanel_->AddText(CurString);
			//
			//// ���� ����ϴ� �ε����� �޼����� �ִ���̿� ������ 
			//// ����� �ؽ�Ʈ ��� ����
			//if (CurPrintTextIndex_ == SaveTextLen)
			//{
			//	// ���� Flag On
			//	MessageLoadEnd_ = true;

			//	// ���۰��� Flag Off
			//	MessageLoadStart_ = false;
			//}

			//++CurPrintTextIndex_;
		}
	}
}

void NPC_MessageView::SetNPCMessage(const std::string& _Text)
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// ��µǴ� �޼��� ���
	SaveMsgText_ = _Text;

	// �޼����� ���ڼ��� �̿��Ͽ� �ؽ�Ʈ��� ���� ���� ����(���ٴ� �ִ���ڼ� 35)
	int CurTextTotSize = static_cast<int>(SaveMsgText_.size());
	int TextLineCnt = (CurTextTotSize / 35) %  35;

	// ����������� �� ����
	PrintTextList_.clear();
	int Index = 0;
	for (int i = 0; i < TextLineCnt + 1; ++i)
	{
		GameEngineUIRenderer* NewTextRenderer = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
		NewTextRenderer->SetImage("MessageView_Panel.png");
		NewTextRenderer->SetAlpha(0.f);
		NewTextRenderer->GetTransform()->SetLocalScaling(float4(272.f, 93.f));
		NewTextRenderer->GetTransform()->SetLocalPosition(MsgPanel_->GetTransform()->GetLocalPosition());

		// Text ����
		std::string PrintText = "";


		NewTextRenderer->TextSetting("diablo", PrintText, 12.f, FW1_LEFT | FW1_VCENTER, float4::WHITE, float4(-132.f, -38.f), 35);

		++Index;
	}
}

void NPC_MessageView::FirstInteractionActive()
{
	// NPC ���� ��ȣ�ۿ�� ȣ��Ǿ� �޼��� ���
	On();

	// �Էµ� �޼��� ��� ���� Flag On
	MessageLoadStart_ = true;
}

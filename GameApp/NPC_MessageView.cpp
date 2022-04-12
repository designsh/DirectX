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
			// �޼�������� �����Ҷ�
			if (false == PrintTextList_.empty())
			{
				// ���� ����ؾ��ϴ� ���μ��� �ִ�ġ�� �Ѿ��
				if (static_cast<int>(PrintTextList_.size()) <= CurTextLineIdx_)
				{
					MessagePrintDelayTime_ = 1.f;

					// �ش� �޼��� ������� Flag On / ��½��� Flag Off
					MessageLoadStart_ = false;
					MessageLoadEnd_ = true;
				}

				// �ƴ϶�� CurTextLineIdx_ - 1



				// �����ε��������� �ؽ�Ʈ�� ��� On�����̰�, �����ε����� On�̵Ǹ鼭 
				// �����ε��������� �ؽ�Ʈ���� ��ǥ�����̾ƴϸ� ��������� �̵��� �ϰ�, 
				// ��ǥ������ �����ϸ� Off ���·� ��ȯ�� ���ÿ� �ʱ���ġ�� ��ġ�� ������Ѵ�.








				// TextEndPosArrive();


			}

			// ������ �ð� �ʱ�ȭ
			MessagePrintDelayTime_ = 1.f;

			// ���� ���� �ε��� ����
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

	// ��µǴ� �޼��� ���
	SaveMsgText_ = _Text;

	// �޼����� ���ڼ��� �̿��Ͽ� �ؽ�Ʈ��� ���� ���� ����(���ٴ� �ִ���ڼ� 35)
	int CurTextTotSize = static_cast<int>(SaveMsgText_.size());
	int TextLineCnt = (CurTextTotSize / 35) %  35;

	// ����������� �� ����
	int Index = 0;
	PrintTextList_.clear();
	for (int i = 0; i < TextLineCnt + 1; ++i)
	{
		GameEngineUIRenderer* NewTextRenderer = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
		NewTextRenderer->SetImage("MessageView_Panel.png");
		NewTextRenderer->SetAlpha(0.f);
		NewTextRenderer->GetTransform()->SetLocalScaling(float4(272.f, 93.f));
		NewTextRenderer->GetTransform()->SetLocalPosition(MsgPanel_->GetTransform()->GetLocalPosition());

		// ��ü���ڿ����� Ư���κ� Text �߶� �ؽ�Ʈ ����
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
	// NPC ���� ��ȣ�ۿ�� ȣ��Ǿ� �޼��� ���
	On();

	// �Էµ� �޼��� ��� ���� Flag On
	MessageLoadStart_ = true;
}

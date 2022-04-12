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
		// CurTextLineIdx_������ ���ε��� ���� �̵���Ų��.
		// ��, ��ǥ��ġ�� ������ �ؽ�Ʈ������ �ʱ���ġ�� ������ϰ�, Off ���·� ��ȯ�Ѵ�.
		for (int i = 0; i < CurTextLineIdx_; ++i)
		{
			if (true == PrintTextList_[i]->IsUpdate())
			{
				// ���� �̵��ϹǷ� y�� ���Ͽ� ��ǥ������ �Ѿ�� �ش� �ؽ�Ʈ������ �ʱ�����ϰ� Off
				if (TextMoveEndPos_.y <= PrintTextList_[i]->GetTransform()->GetLocalPosition().y)
				{
					// �ʱ� ��ġ�� ���� �� 
					float4 ParentPos = MsgPanel_->GetTransform()->GetLocalPosition();
					PrintTextList_[i]->GetTransform()->SetLocalPosition(float4(ParentPos.x, ParentPos.y - 38.f));

					// Off ���� ��ȯ
					PrintTextList_[i]->Off();

					// �������ε����� �ؽ�Ʈ������ ǥ�� �� �̵��Ϸ�� �ش� �޼���â Off ó��
					if (i + 1 == CurTextLineIdx_)
					{
						CurTextLineIdx_ = 0;
						MessageLoadStart_ = false;
						MessageLoadEnd_ = true;
						return;
					}
				}
				else // �ƴ϶�� �̵�
				{
					float4 CurPos = PrintTextList_[i]->GetTransform()->GetLocalPosition();
					CurPos += (float4::UP * TextMoveSpeed_ * _DeltaTime);
					PrintTextList_[i]->GetTransform()->SetLocalPosition(CurPos);
				}
			}
		}

		// ��, �������ΰ� ��������� ��ġ�� ���Ͽ� �����Ÿ��� �Ѿ�� On
		if (0 < CurTextLineIdx_ && CurTextLineIdx_ < static_cast<int>(PrintTextList_.size()))
		{
			float4 PrevPos = PrintTextList_[CurTextLineIdx_ - 1]->GetTransform()->GetLocalPosition();
			float4 CurPos = PrintTextList_[CurTextLineIdx_]->GetTransform()->GetLocalPosition();
			if (CurPos.y + 10.f <= PrevPos.y)
			{
				// �������ε��� ��� �̵��ߴٸ� ���� ������ On
				PrintTextList_[CurTextLineIdx_]->On();

				// ���� ���� �ε��� ����
				++CurTextLineIdx_;
			}
		}

		if(0 == CurTextLineIdx_)
		{
			PrintTextList_[0]->On();

			// ���� ���� �ε��� ����
			++CurTextLineIdx_;
		}
	}
}

void NPC_MessageView::CreateNPCMessageTextList(const std::string& _Text)
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// ��µǴ� �޼��� ���
	SaveMsgText_ = _Text;

	// �޼����� ���ڼ��� �̿��Ͽ� �ؽ�Ʈ��� ���� ���� ����(���ٴ� �ִ���ڼ� 30)
	int CurTextTotSize = static_cast<int>(SaveMsgText_.size());
	int TextLineCnt = (CurTextTotSize / 30) %  30;

	// �ؽ�Ʈ ���� �Ҹ���� üũ
	float4 ParentPos = MsgPanel_->GetTransform()->GetLocalPosition();
	TextMoveEndPos_ = float4(ParentPos.x, ParentPos.y + 38.f);

	// ����������� �� ����
	int Index = 0;
	PrintTextList_.clear();
	for (int i = 0; i < TextLineCnt + 1; ++i)
	{
		GameEngineUIRenderer* NewTextRenderer = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
		NewTextRenderer->SetImage("MessageView_Panel.png");
		NewTextRenderer->SetAlpha(0.f);
		NewTextRenderer->GetTransform()->SetLocalScaling(float4(272.f, 93.f));
		NewTextRenderer->GetTransform()->SetLocalPosition(float4(ParentPos.x, ParentPos.y - 38.f));

		// ��ü���ڿ����� Ư���κ� Text �߶� �ؽ�Ʈ ����
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
	// �޼�������� �����Ҷ�
	if (false == PrintTextList_.empty())
	{
		// NPC ���� ��ȣ�ۿ�� ȣ��Ǿ� �޼��� ���
		On();

		// �Էµ� �޼��� ��� ���� Flag On / ��� ���� Flag Off
		MessageLoadStart_ = true;
		MessageLoadEnd_ = false;
	}
	else // �ؽ�Ʈ����� ���������ʴٸ�
	{
		// �ٷ� ��� ���� Flag Off / ��� ���� Flag On
		MessageLoadStart_ = false;
		MessageLoadEnd_ = true;
	}
}

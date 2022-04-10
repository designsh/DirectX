#include "PreCompile.h"
#include "NPC_MessageView.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

NPC_MessageView::NPC_MessageView() :
	MsgPanel_(nullptr)
{
}

NPC_MessageView::~NPC_MessageView()
{
}

void NPC_MessageView::Start()
{
	// �޼��� �ǳ� ������ ����
	MsgPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	MsgPanel_->SetImage("MessageView_Panel.png");
	MsgPanel_->GetTransform()->SetLocalScaling(float4(272.f, 93.f));
	MsgPanel_->Off();
}

void NPC_MessageView::Update(float _DeltaTime)
{
	// ��µ� �޼��� ��¿Ϸ�� �ش� NPC�� �޴������� ���� Flag �۽�


}

void NPC_MessageView::SetNPCMessage(const std::string& _Text)
{
	// ��µǴ� �޼��� ���

	
}

void NPC_MessageView::FirstInteractionActive()
{
	// NPC ���� ��ȣ�ۿ�� ȣ��Ǿ� �޼��� ���
	MsgPanel_->On();

	// �Էµ� �޼��� ��� ����

}

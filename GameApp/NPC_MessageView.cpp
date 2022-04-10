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
	// 메세지 판넬 렌더러 생성
	MsgPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	MsgPanel_->SetImage("MessageView_Panel.png");
	MsgPanel_->GetTransform()->SetLocalScaling(float4(272.f, 93.f));
	MsgPanel_->Off();
}

void NPC_MessageView::Update(float _DeltaTime)
{
	// 출력된 메세지 출력완료시 해당 NPC의 메뉴도출을 위한 Flag 송신


}

void NPC_MessageView::SetNPCMessage(const std::string& _Text)
{
	// 출력되는 메세지 등록

	
}

void NPC_MessageView::FirstInteractionActive()
{
	// NPC 최초 상호작용시 호출되어 메세지 출력
	MsgPanel_->On();

	// 입력된 메세지 출력 시작

}

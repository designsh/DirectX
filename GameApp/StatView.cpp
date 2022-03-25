#include "PreCompile.h"
#include "StatView.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayerInfomation.h"

StatView::StatView() :
	Panel_(nullptr),
	PlayerID_(nullptr)
{
}

StatView::~StatView()
{
}

void StatView::Start()
{
	// �����÷��̾� ���� Get
	const MainPlayerInfo* PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfo();

	// Player_StateView_Panel
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("Player_StateView_Panel.png");
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();

	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();

	// �÷��̾� ����â �ǳ�
	Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	Panel_->SetImage("Player_StateView_Panel.png");
	Panel_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x - WindowHarfSize.x, 24.f));

	// �÷��̾� Text������ ���� �ǳ�
	std::string ID = PlayerInfo->ID;
	PlayerID_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	//PlayerID_->TextSetting("diablo", ID, 20, FW1_VCENTER | FW1_CENTER, float4::WHITE);
	PlayerID_->TextSetting("diablo", "TEST", 20, FW1_VCENTER | FW1_CENTER, float4::WHITE, float4(), 15);
	


	Off();
}

void StatView::Update(float _DeltaTime)
{
}

#include "PreCompile.h"
#include "TitleLevelMoveBtn.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

TitleLevelMoveBtn::TitleLevelMoveBtn() :
	PrevMenuBtn_(nullptr)
{
}

TitleLevelMoveBtn::~TitleLevelMoveBtn()
{
}

void TitleLevelMoveBtn::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	GameEngineTexture* ButtonImage = GameEngineTextureManager::GetInst().Find("ShortButton_Stay.png");
	float4 TextureSize = ButtonImage->GetTextureSize();

	// 추후 버튼UI 만들면 변경예정
	PrevMenuBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(OrderGroup::UI0));
	PrevMenuBtn_->SetImage("ShortButton_Stay.png", float4(150.f, 40.f));
	PrevMenuBtn_->GetTransform()->SetLocalPosition(float4(-WindowSize.ihx() + 130.f, -WindowSize.ihy() + 60.f));
}

void TitleLevelMoveBtn::Update(float _DeltaTime)
{
	// 마우스와 충돌하였으며, 마우스 왼쪽버튼 클릭시 타이틀 화면으로 이동

}

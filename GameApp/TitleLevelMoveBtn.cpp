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

	// ���� ��ưUI ����� ���濹��
	PrevMenuBtn_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(OrderGroup::UI0));
	PrevMenuBtn_->SetImage("ShortButton_Stay.png", float4(150.f, 40.f));
	PrevMenuBtn_->GetTransform()->SetLocalPosition(float4(-WindowSize.ihx() + 130.f, -WindowSize.ihy() + 60.f));
}

void TitleLevelMoveBtn::Update(float _DeltaTime)
{
	// ���콺�� �浹�Ͽ�����, ���콺 ���ʹ�ư Ŭ���� Ÿ��Ʋ ȭ������ �̵�

}

#include "PreCompile.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

BottomStateBar::BottomStateBar() :
	Panel_(nullptr)
{
}

BottomStateBar::~BottomStateBar()
{
}

void BottomStateBar::Start()
{
	GameEngineTexture* BottomStateBarImage = GameEngineTextureManager::GetInst().Find("Player_BottomStatBar_UI.png");
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();
	float4 ImageSize = BottomStateBarImage->GetTextureSize();
	float4 ImageHarfSize = ImageSize.halffloat4();

	// �ϴܻ��¹� Ʋ
	Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI2));
	Panel_->SetImage("Player_BottomStatBar_UI.png", float4(WindowSize.x, ImageSize.y));
	Panel_->GetTransform()->SetLocalPosition(float4(0.f, ImageHarfSize.y - WindowHarfSize.y));

	// ���� ���� ����
	
	// ���ʹ��� Ȱ��ȭ ��ų��ư

	// �����ʹ��� Ȱ��ȭ ��ų��ư

	// ���¹̳� Ȱ��/��Ȱ�� ��ư

	// ���¹̳� ProgressBar

	// ����ĭ�浹ü?

	// �̴ϸ޴�����

}

void BottomStateBar::Update(float _DeltaTime)
{
}

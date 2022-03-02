#include "PreCompile.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineUIRenderer.h>

BottomStateBar::BottomStateBar() :
	BottomStateBar_(nullptr)
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
	float4 ImageSize = BottomStateBarImage->GetImageSize();
	float4 ImageHarfSize = ImageSize.halffloat4();

	// �ϴܻ��¹� Ʋ
	BottomStateBar_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	BottomStateBar_->SetRenderingPipeLine("Texture");
	BottomStateBar_->ShaderHelper.SettingTexture("Tex", "Player_BottomStatBar_UI.png");
	BottomStateBar_->ShaderHelper.SettingConstantBufferSet("TextureCutData", float4(0.f, 0.f, 1.f, 1.f));
	BottomStateBar_->GetTransform()->SetLocalScaling(float4(WindowSize.x, ImageSize.y));
	BottomStateBar_->GetTransform()->SetLocalPosition(float4(0.f, ImageHarfSize.y - WindowHarfSize.y));

	// ���� �Ѱ��� ���� �ɰ��� �����......
	
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

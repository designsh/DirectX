#include "PreCompile.h"
#include "TitleLogo.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineTransform.h>

TitleLogo::TitleLogo() :
	LogoAnimation_(nullptr)
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Start()
{
	// 400 x 196

	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	GameEngineTexture* LogoTexture = GameEngineTextureManager::GetInst().Find("Title_Logo.png");
	LogoTexture->Cut(30, 1);

	// 로고 애니메이션 렌더러 생성
	LogoAnimation_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	LogoAnimation_->SetImage("Title_Logo.png", float4(550.f, 196.f));
	LogoAnimation_->CreateAnimation("TitleLogoAnimation", 0, 29, 0.1f);
	LogoAnimation_->SetChangeAnimation("TitleLogoAnimation");
	LogoAnimation_->GetTransform()->SetLocalPosition(float4(0.f, 230.f));
	
}

void TitleLogo::Update(float _DeltaTime)
{
}

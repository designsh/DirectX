#include "PreCompile.h"
#include "TitleLogo.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineTransform.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

TitleLogo::TitleLogo() :
	LogoAnimation_(nullptr)
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Start()
{
	GameEngineTexture* LogoTexture = GameEngineTextureManager::GetInst().Find("Title_Logo.png");
	LogoTexture->Cut(30, 1);

	// 로고 애니메이션 렌더러 생성
	LogoAnimation_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(OrderGroup::UI0));
	LogoAnimation_->CreateAnimation("Title_Logo.png", "TitleLogoAnimation", 0, 29, 0.1f);
	LogoAnimation_->SetChangeAnimation("TitleLogoAnimation");
	LogoAnimation_->GetTransform()->SetLocalPosition(float4(0.f, 240.f));
	LogoAnimation_->GetTransform()->SetLocalScaling(float4(550.f, 196.f));
}

void TitleLogo::Update(float _DeltaTime)
{
}

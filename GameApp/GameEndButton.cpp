#include "PreCompile.h"
#include "GameEndButton.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "UserGame.h"

GameEndButton::GameEndButton() :
	EndButton_(nullptr),
	MainCollision_(nullptr)
{
}

GameEndButton::~GameEndButton()
{
}

void GameEndButton::Start()
{
	GameEngineTexture* ButtonImage = GameEngineTextureManager::GetInst().Find("LongButton_Stay.png");
	float4 TextureSize = ButtonImage->GetTextureSize();

	EndButton_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	EndButton_->SetRenderingPipeLine("Texture");
	EndButton_->ShaderHelper.SettingTexture("Tex", "LongButton_Stay.png");
	EndButton_->ShaderHelper.SettingConstantBufferSet("TextureCutData", float4(0.f, 0.f, 1.f, 1.f));
	EndButton_->GetTransform()->SetLocalScaling(float4(430.f, 40.f));
	EndButton_->GetTransform()->SetLocalPosition(float4(0.f, -300.f));

	// 충돌체 생성
	MainCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(OrderGroup::UI0));
	MainCollision_->GetTransform()->SetLocalScaling(float4(430.f, 40.f, 1.0f));
	MainCollision_->GetTransform()->SetLocalPosition(float4(0.f, -300.f));
}

void GameEndButton::Update(float _DeltaTime)
{
	MainCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(OrderGroup::MouseCollider), std::bind(&GameEndButton::GameEndButtonClick, this, std::placeholders::_1));
}

void GameEndButton::GameEndButtonClick(GameEngineCollision* _OtherCollision)
{
	// 마우스와 충돌시
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 게임 종료 => 윈도우 종료
		GameEngineWindow::GetInst().CloseWindow();
	}
}

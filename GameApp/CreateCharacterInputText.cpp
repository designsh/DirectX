#include "PreCompile.h"
#include "CreateCharacterInputText.h"

#include <GameEngine/GameEngineUIRenderer.h>

std::string CreateCharacterInputText::InputID = "";

std::string CreateCharacterInputText::GetInputID()
{
	return InputID;
}

CreateCharacterInputText::CreateCharacterInputText() :
	IDInput_(nullptr)
{
}

CreateCharacterInputText::~CreateCharacterInputText()
{
}

void CreateCharacterInputText::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	GameEngineTexture* InputTextImage = GameEngineTextureManager::GetInst().Find("InputText.png");
	float4 TextureSize = InputTextImage->GetTextureSize();

	// 추후 버튼UI 만들면 변경예정
	IDInput_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	IDInput_->SetRenderingPipeLine("Texture");
	IDInput_->ShaderHelper.SettingTexture("Tex", "InputText.png");
	IDInput_->ShaderHelper.SettingConstantBufferSet("TextureCutData", float4(0.f, 0.f, 1.f, 1.f));
	IDInput_->GetTransform()->SetLocalScaling(float4(150.f, 30.f));
	IDInput_->GetTransform()->SetLocalPosition(float4(0.f, -WindowSize.ihy() + 60.f));
}

void CreateCharacterInputText::Update(float _DeltaTime)
{
	// 마우스와 충돌중이며, 마우스 왼쪽버튼 클릭시 입력창 활성화
	// 활성화된 입력창에 키보드를 이용하여 입력가능
	// 입력마다 InputID에 저장

}

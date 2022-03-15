#include "PreCompile.h"
#include "CreateCharacterInputText.h"

#include <GameEngine/GameEngineUIRenderer.h>


#include "GlobalEnumClass.h"
#include "GlobalValue.h"

std::string CreateCharacterInputText::InputText = "";

std::string CreateCharacterInputText::GetInputID()
{
	return InputText;
}

CreateCharacterInputText::CreateCharacterInputText() :
	IDInput_(nullptr),
	InputBoxActive_(false)
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
	IDInput_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(OrderGroup::UI0));
	IDInput_->SetImage("InputText.png", float4(150.f, 30.f));
	IDInput_->GetTransform()->SetLocalPosition(float4(0.f, -WindowSize.ihy() + 60.f));
}

void CreateCharacterInputText::Update(float _DeltaTime)
{
	// 마우스와 충돌중이며, 마우스 왼쪽버튼 클릭시 입력창 활성화
	// 활성화된 입력창에 키보드를 이용하여 입력가능상태로 전환 : InputBoxActive_ = true;
	



	// 입력가능 상태라면 입력마다 InputID에 저장
	if (true == InputBoxActive_)
	{
		CharacterIDInput();
	}
}

void CreateCharacterInputText::CharacterIDInput()
{
	// 키보드 키 입력을 받아와서 InputID에 저장하며,
	// InputID를 실시간으로 업데이트하여 화면에 표시
	// 글자수제한 걸기!!!



}

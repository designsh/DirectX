#include "PreCompile.h"
#include "CreateCharacterInputText.h"

#include <GameEngine/GameEngineUIRenderer.h>

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

	// ���� ��ưUI ����� ���濹��
	IDInput_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	IDInput_->SetRenderingPipeLine("Texture");
	IDInput_->ShaderHelper.SettingTexture("Tex", "InputText.png");
	IDInput_->ShaderHelper.SettingConstantBufferSet("TextureCutData", float4(0.f, 0.f, 1.f, 1.f));
	IDInput_->GetTransform()->SetLocalScaling(float4(150.f, 30.f));
	IDInput_->GetTransform()->SetLocalPosition(float4(0.f, -WindowSize.ihy() + 60.f));
}

void CreateCharacterInputText::Update(float _DeltaTime)
{
	// ���콺�� �浹���̸�, ���콺 ���ʹ�ư Ŭ���� �Է�â Ȱ��ȭ
	// Ȱ��ȭ�� �Է�â�� Ű���带 �̿��Ͽ� �Է°��ɻ��·� ��ȯ : InputBoxActive_ = true;
	



	// �Է°��� ���¶�� �Է¸��� InputID�� ����
	if (true == InputBoxActive_)
	{
		CharacterIDInput();
	}
}

void CreateCharacterInputText::CharacterIDInput()
{
	// Ű���� Ű �Է��� �޾ƿͼ� InputID�� �����ϸ�,
	// InputID�� �ǽð����� ������Ʈ�Ͽ� ȭ�鿡 ǥ��
	// ���ڼ����� �ɱ�!!!



}

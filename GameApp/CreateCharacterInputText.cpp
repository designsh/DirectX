#include "PreCompile.h"
#include "CreateCharacterInputText.h"

#include "ClassSelectObject.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

std::string CreateCharacterInputText::InputText = "";

std::string CreateCharacterInputText::GetInputID()
{
	return InputText;
}

CreateCharacterInputText::CreateCharacterInputText() :
	IDInput_(nullptr),
	IDCaret_(nullptr),
	CurCaretIndex_(0),
	InputText_{}
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

	// InputText ID �Է�â
	IDInput_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	IDInput_->SetImage("InputText.png", float4(169.f, 26.f, 1.f));
	IDInput_->GetTransform()->SetLocalPosition(float4(0.f, -WindowSize.ihy() + 60.f));

	// Text(max : 15)
	IDInput_->TextSetting("diablo", InputText_, 15, FW1_VCENTER | FW1_LEFT, float4::WHITE, float4(-82.5f, 0.f, 0.f), ID_MAX_LEN);

	// InputText ID �Է�â�� Caret
	//IDCaret_ = CreateTransformComponent<GameEngineRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	
}

void CreateCharacterInputText::Update(float _DeltaTime)
{
	// ����׿�
	DebugRender();

	// �Է°��� ���¶�� �Է¸��� InputID�� ����
	if (JobType::None != ClassSelectObject::GetSelectClass())
	{
		CharacterIDInput();
	}
	else // ���������� �Ǿ������ʴٸ� Ű�����Է� ���� Ŭ����
	{
		if (false == KeyboardClass::GetInst().CharBufferIsEmpty())
		{
			KeyboardClass::GetInst().DeleteCharBuffer();
		}
	}
}

void CreateCharacterInputText::DebugRender()
{
}

void CreateCharacterInputText::ChangeStartReset()
{
	// ���� �Էµ� ID�� �����Ѵٸ� ����
	IDInput_->AllDelText();
}

void CreateCharacterInputText::CharacterIDInput()
{
	// Ű���� Ű �Է��� �޾ƿͼ� InputID�� �����ϸ�,
	// InputID�� �ǽð����� ������Ʈ�Ͽ� ȭ�鿡 ǥ��
	// ���ڼ����� �ɱ�!!!

	// �Ϲ� Ű�̸� AddText() ȣ��
	while (false == KeyboardClass::GetInst().CharBufferIsEmpty())
	{
		std::string SetStr = "";
		unsigned char ReadChar = KeyboardClass::GetInst().ReadChar();
		SetStr += ReadChar;
		IDInput_->AddText(SetStr);
	}

	// �齺���̽� Ű�̸� DelText() ȣ��


}

void CreateCharacterInputText::AddText(const std::string& _Text)
{
	// ���ڿ� �߰� ���н� �����޼����˾� ����
	if (false == IDInput_->AddText(_Text))
	{
		std::string ErrMsg = "The number of characters that can be entered has been exceeded!!";

		// �����޼���â ����


		return;
	}

	// ���� �Էµ� ���ڿ��� ������ ����
	if (false == InputText.empty())
	{
		InputText.clear();
	}
	InputText = IDInput_->GetPrintText();

	// �Էµ� ���� ���տϷ��̹Ƿ� Ű���� ���� Ŭ����
	KeyboardClass::GetInst().DeleteCharBuffer();

	// ĳ�� ��ġ �̵�
	int CurTextLen = IDInput_->GetPrintTextLen();
	AddCaretIndex(CurTextLen + 1);
}

void CreateCharacterInputText::DelText()
{
	// ���ڿ� ���� ���н� �����޼����˾� ����
	if (false == IDInput_->DelText())
	{
		std::string ErrMsg = "No ID entered. Please enter ID.";

		// �����޼���â ����


		return;
	}

	// ĳ�� ��ġ �̵�
	int CurTextLen = IDInput_->GetPrintTextLen();
	DelCaretIndex(CurTextLen - 1);
}

void CreateCharacterInputText::SetCaretIndex()
{
	// �ʱ� ĳ����ġ ����(0)
	CurCaretIndex_ = 0;
}

void CreateCharacterInputText::AddCaretIndex(int _Index)
{

}

void CreateCharacterInputText::DelCaretIndex(int _Index)
{
}

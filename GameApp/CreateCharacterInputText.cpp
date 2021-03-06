#include "PreCompile.h"
#include "CreateCharacterInputText.h"

#include "ClassSelectObject.h"
#include "ErrorMsgPopup.h"

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

	// InputText ID 입력창
	IDInput_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	IDInput_->SetImage("InputText.png", float4(169.f, 26.f, 1.f));
	IDInput_->GetTransform()->SetLocalPosition(float4(0.f, -WindowSize.ihy() + 60.f));

	// Text(max : 15)
	IDInput_->TextSetting("diablo", InputText_, 15, FW1_VCENTER | FW1_LEFT, float4::WHITE, float4(-82.5f, 0.f, 0.f), ID_MAX_LEN);

	// InputText ID 입력창의 Caret
	//IDCaret_ = CreateTransformComponent<GameEngineRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	
	// 전용 키 생성
	if (false == GameEngineInput::GetInst().IsKey("Delete_IDText"))
	{
		GameEngineInput::GetInst().CreateKey("Delete_IDText", VK_BACK);
	}
}

void CreateCharacterInputText::Update(float _DeltaTime)
{
	// 디버그용
	DebugRender();

	// 입력가능 상태라면 입력마다 InputID에 저장
	if (JobType::None != ClassSelectObject::GetSelectClass())
	{
		CharacterIDInput();
	}
	else // 직업선탱이 되어있지않다면 키보드입력 버퍼 클리어
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
	// 현재 입력된 ID가 존재한다면 삭제
	IDInput_->AllDelText();
}

void CreateCharacterInputText::CharacterIDInput()
{
	// 키보드 키 입력을 받아와서 InputID에 저장하며,
	// InputID를 실시간으로 업데이트하여 화면에 표시
	// 글자수제한 걸기!!!

	// 일반 키이면 AddText() 호출
	while (false == KeyboardClass::GetInst().CharBufferIsEmpty())
	{
		std::string SetStr = "";
		unsigned char ReadChar = KeyboardClass::GetInst().ReadChar();
		SetStr += ReadChar;
		AddText(SetStr);
	}

	// 백스페이스 키이면 DelText() 호출
	if (true == GameEngineInput::GetInst().Down("Delete_IDText"))
	{
		DelText();
	}
}

void CreateCharacterInputText::AddText(const std::string& _Text)
{
	// 문자열 추가 실패시 에러메세지팝업 생성
	if (false == IDInput_->AddText(_Text))
	{
		// 입력가능한 글자수 초과 에러창 생성
		ErrorMsgPopup* ErrorMsg = GetLevel()->CreateActor<ErrorMsgPopup>();
		ErrorMsg->ErrorMsgPopupActive("Excess number of letters!!");

		return;
	}

	// 현재 입력된 문자열을 전역에 저장
	if (false == InputText.empty())
	{
		InputText.clear();
	}
	InputText = IDInput_->GetPrintText();

	// 입력된 문자 병합완료이므로 키보드 버퍼 클리어
	KeyboardClass::GetInst().DeleteCharBuffer();

	// 캐럿 위치 이동
	int CurTextLen = IDInput_->GetPrintTextLen();
	AddCaretIndex(CurTextLen + 1);
}

void CreateCharacterInputText::DelText()
{
	// 문자열 삭제 실패시 에러메세지팝업 생성
	if (false == IDInput_->DelText())
	{
		std::string ErrMsg = "No ID entered. Please enter ID.";

		// 에러메세지창 생성


		return;
	}
	InputText = IDInput_->GetPrintText();

	// 캐럿 위치 이동
	int CurTextLen = IDInput_->GetPrintTextLen();
	DelCaretIndex(CurTextLen - 1);
}

void CreateCharacterInputText::SetCaretIndex()
{
	// 초기 캐럿위치 지정(0)
	CurCaretIndex_ = 0;
}

void CreateCharacterInputText::AddCaretIndex(int _Index)
{

}

void CreateCharacterInputText::DelCaretIndex(int _Index)
{
}

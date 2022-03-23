#include "PreCompile.h"
#include "CreateCharacterInputText.h"

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
	ActiveCollider_(nullptr),
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

	IDInput_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	IDInput_->SetImage("InputText.png", float4(169.f, 26.f, 1.f));
	IDInput_->GetTransform()->SetLocalPosition(float4(0.f, -WindowSize.ihy() + 60.f));

	// Text(max : 15)
	IDInput_->TextSetting("diablo", "", 15, FW1_VCENTER | FW1_LEFT, float4::WHITE, float4(-82.5f, 0.f, 0.f));

	ActiveCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	ActiveCollider_->GetTransform()->SetLocalScaling(float4(169.f, 26.f, 1.f));
	ActiveCollider_->GetTransform()->SetLocalPosition(IDInput_->GetTransform()->GetLocalPosition());
}

void CreateCharacterInputText::Update(float _DeltaTime)
{
	// 디버그용
	DebugRender();

	// 마우스와 충돌체크
	ActiveCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&CreateCharacterInputText::InputBoxActive, this, std::placeholders::_1));
	
	// 입력가능 상태라면 입력마다 InputID에 저장
	if (true == InputBoxActive_)
	{
		CharacterIDInput();
	}
}

void CreateCharacterInputText::ChangeStartReset()
{
	// 기존 입력 ID 삭제
	InputText.clear();

	// ID 입력창 비활성화
	InputBoxActive_ = false;
}

void CreateCharacterInputText::DebugRender()
{
	GetLevel()->PushDebugRender(ActiveCollider_->GetTransform(), CollisionType::Rect);
}

void CreateCharacterInputText::InputBoxActive(GameEngineCollision* _OtherCollision)
{
	// 마우스 왼쪽버튼 클릭시 ID입력창 활성화
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		if (false == InputBoxActive_)
		{
			InputBoxActive_ = true;
		}
	}
}

void CreateCharacterInputText::CharacterIDInput()
{
	// 키보드 키 입력을 받아와서 InputID에 저장하며,
	// InputID를 실시간으로 업데이트하여 화면에 표시
	// 글자수제한 걸기!!!



}

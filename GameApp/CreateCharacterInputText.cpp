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

	IDInput_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(OrderGroup::UI0));
	IDInput_->SetImage("InputText.png", float4(150.f, 30.f));
	IDInput_->GetTransform()->SetLocalPosition(float4(0.f, -WindowSize.ihy() + 60.f));

	ActiveCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(OrderGroup::UI0_Collider));
	ActiveCollider_->GetTransform()->SetLocalScaling(float4(150.f, 30.f, 1.f));
	ActiveCollider_->GetTransform()->SetLocalPosition(IDInput_->GetTransform()->GetLocalPosition());
}

void CreateCharacterInputText::Update(float _DeltaTime)
{
	// 마우스와 충돌체크
	ActiveCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(OrderGroup::MouseCollider), std::bind(&CreateCharacterInputText::InputBoxActive, this, std::placeholders::_1));
	
	
	// 입력가능 상태라면 입력마다 InputID에 저장
	if (true == InputBoxActive_)
	{
		CharacterIDInput();
	}
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

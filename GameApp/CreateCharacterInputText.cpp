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
	// ����׿�
	DebugRender();

	// ���콺�� �浹üũ
	ActiveCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&CreateCharacterInputText::InputBoxActive, this, std::placeholders::_1));
	
	// �Է°��� ���¶�� �Է¸��� InputID�� ����
	if (true == InputBoxActive_)
	{
		CharacterIDInput();
	}
}

void CreateCharacterInputText::ChangeStartReset()
{
	// ���� �Է� ID ����
	InputText.clear();

	// ID �Է�â ��Ȱ��ȭ
	InputBoxActive_ = false;
}

void CreateCharacterInputText::DebugRender()
{
	GetLevel()->PushDebugRender(ActiveCollider_->GetTransform(), CollisionType::Rect);
}

void CreateCharacterInputText::InputBoxActive(GameEngineCollision* _OtherCollision)
{
	// ���콺 ���ʹ�ư Ŭ���� ID�Է�â Ȱ��ȭ
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
	// Ű���� Ű �Է��� �޾ƿͼ� InputID�� �����ϸ�,
	// InputID�� �ǽð����� ������Ʈ�Ͽ� ȭ�鿡 ǥ��
	// ���ڼ����� �ɱ�!!!



}

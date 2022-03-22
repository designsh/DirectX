#include "PreCompile.h"
#include "CreateCharacterLevel.h"

#include "CreateCharacterBackDrop.h"
#include "CreateCharacterFireObject.h"
#include "CurPlayerGameStartButton.h"
#include "TitleLevelMoveBtn.h"
#include "CreateCharacterInputText.h"
#include "ClassSelectObject.h"
#include "MouseObject.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"
#include "GlobalValue.h"

CreateCharacterLevel::CreateCharacterLevel() :
	IDInputTextBox_(nullptr),
	GameStartBtn_(nullptr),
	PrevMenuBtn_(nullptr),
	NecromancerClass_(nullptr)
{
}

CreateCharacterLevel::~CreateCharacterLevel()
{
}

void CreateCharacterLevel::ClassImageCutting()
{
	// =============================================== ��ũ�θǼ� =============================================== // 
	// ��ü
	GameEngineTexture* Entity_NotSelDefault = GameEngineTextureManager::GetInst().Find("Nec_Entity_NotSelDefault.png");
	Entity_NotSelDefault->Cut(12, 1);

	GameEngineTexture* Entity_SelDefault = GameEngineTextureManager::GetInst().Find("Nec_Entity_SelDefault.png");
	Entity_SelDefault->Cut(12, 1);

	GameEngineTexture* Entity_SelDeslect = GameEngineTextureManager::GetInst().Find("Nec_Entity_SelDeslect.png");
	Entity_SelDeslect->Cut(28, 1);

	GameEngineTexture* Entity_SelStart = GameEngineTextureManager::GetInst().Find("Nec_Entity_SelStart.png");
	Entity_SelStart->Cut(38, 1);

	// ����Ʈ
	GameEngineTexture* Effect_NotSelDefault = GameEngineTextureManager::GetInst().Find("Nec_Effect_NotSelDefault.png");
	Effect_NotSelDefault->Cut(12, 1);

	GameEngineTexture* Effect_SelDefault = GameEngineTextureManager::GetInst().Find("Nec_Effect_SelDefault.png");
	Effect_SelDefault->Cut(12, 1);

	GameEngineTexture* Effect_SelDeslect = GameEngineTextureManager::GetInst().Find("Nec_Effect_SelDeslect.png");
	Effect_SelDeslect->Cut(28, 1);

	GameEngineTexture* Effect_SelStart = GameEngineTextureManager::GetInst().Find("Nec_Effect_SelStart.png");
	Effect_SelStart->Cut(38, 1);

	// ================================================= �Ƹ��� ================================================= //
	 
	// ================================================ �Ҽ����� ================================================ // 
	
	// ================================================ �ٹٸ��� ================================================ // 
	
	// ================================================= �ȶ�� ================================================= //
}

void CreateCharacterLevel::LevelChangeEndEvent()
{
	// ������� Off
}

void CreateCharacterLevel::LevelChangeStartEvent()
{
	// ��������� �������͵��� �ʿ��׸� ����
	IDInputTextBox_->ChangeStartReset();
	GameStartBtn_->ChangeStartReset();
	PrevMenuBtn_->ChangeStartReset();
	NecromancerClass_->ChangeStartReset();

	// ������� On
}

void CreateCharacterLevel::LevelStart()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// ������ ����(�̹���)
	CreateCharacterBackDrop* BackDrop = CreateActor<CreateCharacterBackDrop>();

	// ķ�����̾������Ʈ ����(�ִϸ��̼�)
	CreateCharacterFireObject* Fire = CreateActor<CreateCharacterFireObject>();
	//Fire->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -1.f));

	// ID �Է�â
	IDInputTextBox_ = CreateActor<CreateCharacterInputText>();

	// ���۹�ư(�̹��� + �ؽ�Ʈ) -> �ε����� �̵�
	GameStartBtn_ = CreateActor<CurPlayerGameStartButton>();

	// ������ư(�̹��� + �ؽ�Ʈ) -> Ÿ��Ʋ���� �̵�
	PrevMenuBtn_ = CreateActor<TitleLevelMoveBtn>();

	// �������ÿ� �ִϸ��̼�
	ClassImageCutting();

	// ��ũ�θǼ�(�ӽ�)
	NecromancerClass_ = CreateActor<ClassSelectObject>();
	NecromancerClass_->CreateClassRenderer(float4(0.f, 0.f), JobType::Necromancer);
	NecromancerClass_->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -1.f));

	// ���� ���콺 ����
	MouseObject* MainMouse = CreateActor<MouseObject>();
	MainMouse->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());
	GlobalValue::CurMouse = MainMouse;
}

void CreateCharacterLevel::LevelUpdate(float _DeltaTime)
{
	// �׽�Ʈ��
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("LoadingLevel");
	}
}


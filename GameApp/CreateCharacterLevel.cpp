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

CreateCharacterLevel::CreateCharacterLevel()
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
	// ������� On
}

void CreateCharacterLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// ������ ����(�̹���)
	CreateCharacterBackDrop* BackDrop = CreateActor<CreateCharacterBackDrop>();

	// ķ�����̾������Ʈ ����(�ִϸ��̼�)
	CreateCharacterFireObject* Fire = CreateActor<CreateCharacterFireObject>();

	// ID �Է�â
	CreateCharacterInputText* IDInputTextBox = CreateActor<CreateCharacterInputText>();

	// ���۹�ư(�̹��� + �ؽ�Ʈ) -> �ε����� �̵�
	CurPlayerGameStartButton* GameStartBtn = CreateActor<CurPlayerGameStartButton>();

	// ������ư(�̹��� + �ؽ�Ʈ) -> Ÿ��Ʋ���� �̵�
	TitleLevelMoveBtn* PrevMenuBtn = CreateActor<TitleLevelMoveBtn>();

	// �������ÿ� �ִϸ��̼�
	ClassImageCutting();

	// ��ũ�θǼ�(�ӽ�)
	ClassSelectObject* NecromancerClass = CreateActor<ClassSelectObject>();
	NecromancerClass->CreateClassRenderer(float4(0.f, 0.f), JobType::Necromancer);

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


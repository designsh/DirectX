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
	// =============================================== 네크로맨서 =============================================== // 
	// 본체
	GameEngineTexture* Entity_NotSelDefault = GameEngineTextureManager::GetInst().Find("Nec_Entity_NotSelDefault.png");
	Entity_NotSelDefault->Cut(12, 1);

	GameEngineTexture* Entity_SelDefault = GameEngineTextureManager::GetInst().Find("Nec_Entity_SelDefault.png");
	Entity_SelDefault->Cut(12, 1);

	GameEngineTexture* Entity_SelDeslect = GameEngineTextureManager::GetInst().Find("Nec_Entity_SelDeslect.png");
	Entity_SelDeslect->Cut(28, 1);

	GameEngineTexture* Entity_SelStart = GameEngineTextureManager::GetInst().Find("Nec_Entity_SelStart.png");
	Entity_SelStart->Cut(38, 1);

	// 이펙트
	GameEngineTexture* Effect_NotSelDefault = GameEngineTextureManager::GetInst().Find("Nec_Effect_NotSelDefault.png");
	Effect_NotSelDefault->Cut(12, 1);

	GameEngineTexture* Effect_SelDefault = GameEngineTextureManager::GetInst().Find("Nec_Effect_SelDefault.png");
	Effect_SelDefault->Cut(12, 1);

	GameEngineTexture* Effect_SelDeslect = GameEngineTextureManager::GetInst().Find("Nec_Effect_SelDeslect.png");
	Effect_SelDeslect->Cut(28, 1);

	GameEngineTexture* Effect_SelStart = GameEngineTextureManager::GetInst().Find("Nec_Effect_SelStart.png");
	Effect_SelStart->Cut(38, 1);

	// ================================================= 아마존 ================================================= //
	 
	// ================================================ 소서리스 ================================================ // 
	
	// ================================================ 바바리안 ================================================ // 
	
	// ================================================= 팔라딘 ================================================= //
}

void CreateCharacterLevel::LevelChangeEndEvent()
{
	// 배경음악 Off
}

void CreateCharacterLevel::LevelChangeStartEvent()
{
	// 배경음악 On
}

void CreateCharacterLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	// 배경액터 생성(이미지)
	CreateCharacterBackDrop* BackDrop = CreateActor<CreateCharacterBackDrop>();

	// 캠프파이어오브젝트 생성(애니메이션)
	CreateCharacterFireObject* Fire = CreateActor<CreateCharacterFireObject>();

	// ID 입력창
	CreateCharacterInputText* IDInputTextBox = CreateActor<CreateCharacterInputText>();

	// 시작버튼(이미지 + 텍스트) -> 로딩레벨 이동
	CurPlayerGameStartButton* GameStartBtn = CreateActor<CurPlayerGameStartButton>();

	// 이전버튼(이미지 + 텍스트) -> 타이틀레벨 이동
	TitleLevelMoveBtn* PrevMenuBtn = CreateActor<TitleLevelMoveBtn>();

	// 직업선택용 애니메이션
	ClassImageCutting();

	// 네크로맨서(임시)
	ClassSelectObject* NecromancerClass = CreateActor<ClassSelectObject>();
	NecromancerClass->CreateClassRenderer(float4(0.f, 0.f), JobType::Necromancer);

	// 현재 마우스 생성
	MouseObject* MainMouse = CreateActor<MouseObject>();
	MainMouse->GetTransform()->SetLocalPosition(GameEngineInput::GetInst().GetMouse3DPos());
	GlobalValue::CurMouse = MainMouse;
}

void CreateCharacterLevel::LevelUpdate(float _DeltaTime)
{
	// 테스트용
	if (true == GameEngineInput::GetInst().Down("NextScene"))
	{
		UserGame::LevelChange("LoadingLevel");
	}
}


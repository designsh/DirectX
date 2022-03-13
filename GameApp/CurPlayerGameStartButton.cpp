#include "PreCompile.h"
#include "CurPlayerGameStartButton.h"

#include "ClassSelectObject.h"
#include "CreateCharacterInputText.h"
#include "MainPlayerInfomation.h"

#include <GameEngine/GameEngineUIRenderer.h>

#include "UserGame.h"

bool CurPlayerGameStartButton::ClassSelect_ = false;

void CurPlayerGameStartButton::UserClassSelect()
{
	ClassSelect_ = true;
}

void CurPlayerGameStartButton::UserClassDeselect()
{
	ClassSelect_ = false;
}

CurPlayerGameStartButton::CurPlayerGameStartButton() :
	CurPlayerGameStartBtn_(nullptr),
	RenderFlag_(false)
{
}

CurPlayerGameStartButton::~CurPlayerGameStartButton()
{
}

void CurPlayerGameStartButton::Start()
{
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();

	GameEngineTexture* ButtonImage = GameEngineTextureManager::GetInst().Find("ShortButton_Stay.png");
	float4 TextureSize = ButtonImage->GetTextureSize();

	// 추후 버튼UI 만들면 변경예정
	CurPlayerGameStartBtn_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	CurPlayerGameStartBtn_->SetRenderingPipeLine("Texture");
	CurPlayerGameStartBtn_->ShaderHelper.SettingTexture("Tex", "ShortButton_Stay.png");
	CurPlayerGameStartBtn_->ShaderHelper.SettingConstantBufferSet("TextureCutData", float4(0.f, 0.f, 1.f, 1.f));
	CurPlayerGameStartBtn_->GetTransform()->SetLocalScaling(float4(150.f, 40.f));
	CurPlayerGameStartBtn_->GetTransform()->SetLocalPosition(float4(WindowSize.ihx() - 130.f, -WindowSize.ihy() + 60.f));
	CurPlayerGameStartBtn_->Off();
}

void CurPlayerGameStartButton::Update(float _DeltaTime)
{
	// 1. 버튼 활성/비활성 여부 판단
	if (false == RenderFlag_)
	{
		if (true == ClassSelect_)
		{
			CurPlayerGameStartBtn_->On();
			RenderFlag_ = true;
		}
	}
	else
	{
		if (false == ClassSelect_)
		{
			CurPlayerGameStartBtn_->Off();
			RenderFlag_ = false;
		}
	}

	// 2. 마우스와 충돌체크
	// 마우스와 충돌하였으며, 마우스 왼쪽버튼 클릭시
	//MainPlayerInfomation::GetInst().CreateMainPlayerInfo("aaaa", JobType::Necromancer); 함수를 호출하여
	// 메인플레이어 정보도 생성하며 해당 플레이어 정보를 가지는 파일을 생성하고
	// 생성 완료 후 로딩레벨로 전환된다.
	// 단, 이전 플레이어 생성시 사용된 ID를 체크하여 동일한 ID의 파일이 존재하다면 경고창을 화면에 띄우고 레벨전환이 불가하다.
	// GameStartConditionCheck();

}

void CurPlayerGameStartButton::GameStartConditionCheck()
{
	// 현재 선택된 직업(클래스)가 있는지 검사
	if (JobType::None != ClassSelectObject::GetSelectClass())
	{
		// 선택된 직업(클래스)가 있다면 생성 가능한 플레이어 ID인지 검사 후
		// 정상적이라면 플레이어 정보 생성 및 정보파일 저장
		// 비정상이라면 경고창이 화면에 표시되며, 정보 생성 및 레벨전환 불가
		CheckSameID();
	}
}

void CurPlayerGameStartButton::CheckSameID()
{
	bool CheckFlag = false;

	// 버튼클릭 시점에 호출되며, 지정된 경로에 해당 ID와 같은이름이 존재한다면
	// 경고창을 화면에 표시하며, 존재하지않다면 해당 ID로 파일을 생성

	// 1. 버튼클릭 시점에 CreateCharacterInputText에 입력된 Text Get
	std::string CurID = CreateCharacterInputText::GetInputID();
	if (true == CurID.empty()) // 입력한 ID가 없다면 경고창 표시
	{
		// ID를 입력하시오!!!! 경고창 표시


		CheckFlag = true;
	}

	// 2. 해당 ID를 파일명으로 가지는 파일이 존재하는지 탐색
	if (true == DefaultPathFileNameCheck(CurID))
	{
		// 같은 ID의 플레이어가 이미 존재합니다!!!! 경고창 표시


		// 플레이어 정보 생성 실패 Flag On
		CheckFlag = true;
	}

	// 3. 동일한 ID가 없다면 플레이어 정보 생성
	if (false == CheckFlag)
	{
		CreateCurPlayer(CurID);
	}
}

bool CurPlayerGameStartButton::DefaultPathFileNameCheck(const std::string& _PlayerID)
{
	// 생성된 플레이어 파일 경로에 해당 ID의 파일이 존재하면 동일 이름 플레이어가 존재하므로 경고창 표시
	GameEngineDirectory PlayerFileDir;
	PlayerFileDir.MoveParent("DirectX");
	PlayerFileDir.MoveChild("Resources");
	PlayerFileDir.MoveChild("SaveFile");
	if (true == PlayerFileDir.CheckSameFileName(_PlayerID, ".dat"))
	{
		// 동일한 파일명을 찾음
		return true;
	}
	
	return false;
}

void CurPlayerGameStartButton::CreateCurPlayer(const std::string& _PlayerID)
{
	JobType CurClass = ClassSelectObject::GetSelectClass();
	if (JobType::None != CurClass)
	{
		// 메인플레이어 정보 생성 및 해당 플레이어 파일 생성
		MainPlayerInfomation::GetInst().CreateMainPlayerInfo(_PlayerID, CurClass);

		// 생성완료 후 레벨 전환
		UserGame::LevelChange("LoadingLevel");
	}
}

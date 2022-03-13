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

	// ���� ��ưUI ����� ���濹��
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
	// 1. ��ư Ȱ��/��Ȱ�� ���� �Ǵ�
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

	// 2. ���콺�� �浹üũ
	// ���콺�� �浹�Ͽ�����, ���콺 ���ʹ�ư Ŭ����
	//MainPlayerInfomation::GetInst().CreateMainPlayerInfo("aaaa", JobType::Necromancer); �Լ��� ȣ���Ͽ�
	// �����÷��̾� ������ �����ϸ� �ش� �÷��̾� ������ ������ ������ �����ϰ�
	// ���� �Ϸ� �� �ε������� ��ȯ�ȴ�.
	// ��, ���� �÷��̾� ������ ���� ID�� üũ�Ͽ� ������ ID�� ������ �����ϴٸ� ���â�� ȭ�鿡 ���� ������ȯ�� �Ұ��ϴ�.
	// GameStartConditionCheck();

}

void CurPlayerGameStartButton::GameStartConditionCheck()
{
	// ���� ���õ� ����(Ŭ����)�� �ִ��� �˻�
	if (JobType::None != ClassSelectObject::GetSelectClass())
	{
		// ���õ� ����(Ŭ����)�� �ִٸ� ���� ������ �÷��̾� ID���� �˻� ��
		// �������̶�� �÷��̾� ���� ���� �� �������� ����
		// �������̶�� ���â�� ȭ�鿡 ǥ�õǸ�, ���� ���� �� ������ȯ �Ұ�
		CheckSameID();
	}
}

void CurPlayerGameStartButton::CheckSameID()
{
	bool CheckFlag = false;

	// ��ưŬ�� ������ ȣ��Ǹ�, ������ ��ο� �ش� ID�� �����̸��� �����Ѵٸ�
	// ���â�� ȭ�鿡 ǥ���ϸ�, ���������ʴٸ� �ش� ID�� ������ ����

	// 1. ��ưŬ�� ������ CreateCharacterInputText�� �Էµ� Text Get
	std::string CurID = CreateCharacterInputText::GetInputID();
	if (true == CurID.empty()) // �Է��� ID�� ���ٸ� ���â ǥ��
	{
		// ID�� �Է��Ͻÿ�!!!! ���â ǥ��


		CheckFlag = true;
	}

	// 2. �ش� ID�� ���ϸ����� ������ ������ �����ϴ��� Ž��
	if (true == DefaultPathFileNameCheck(CurID))
	{
		// ���� ID�� �÷��̾ �̹� �����մϴ�!!!! ���â ǥ��


		// �÷��̾� ���� ���� ���� Flag On
		CheckFlag = true;
	}

	// 3. ������ ID�� ���ٸ� �÷��̾� ���� ����
	if (false == CheckFlag)
	{
		CreateCurPlayer(CurID);
	}
}

bool CurPlayerGameStartButton::DefaultPathFileNameCheck(const std::string& _PlayerID)
{
	// ������ �÷��̾� ���� ��ο� �ش� ID�� ������ �����ϸ� ���� �̸� �÷��̾ �����ϹǷ� ���â ǥ��
	GameEngineDirectory PlayerFileDir;
	PlayerFileDir.MoveParent("DirectX");
	PlayerFileDir.MoveChild("Resources");
	PlayerFileDir.MoveChild("SaveFile");
	if (true == PlayerFileDir.CheckSameFileName(_PlayerID, ".dat"))
	{
		// ������ ���ϸ��� ã��
		return true;
	}
	
	return false;
}

void CurPlayerGameStartButton::CreateCurPlayer(const std::string& _PlayerID)
{
	JobType CurClass = ClassSelectObject::GetSelectClass();
	if (JobType::None != CurClass)
	{
		// �����÷��̾� ���� ���� �� �ش� �÷��̾� ���� ����
		MainPlayerInfomation::GetInst().CreateMainPlayerInfo(_PlayerID, CurClass);

		// �����Ϸ� �� ���� ��ȯ
		UserGame::LevelChange("LoadingLevel");
	}
}

#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �з� : �÷��̾� UI
// �뵵 : ��ųâ
// ���� : ��ų������
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_SkillIcon;
class SkillView : public GameEngineActor
{
private:
	static SkillPageNo CurSkillPage;

public:
	static SkillPageNo GetCurSkillPage();
	static void SetCurSkillPage(SkillPageNo _SkillPageNo);

private:	// member Var
	GameEngineUIRenderer* PanelRenderer_;						// ��ųâ �ǳ� ������

private: // ��ų������
	GameEngineUIRenderer* SkillPagePanel_[static_cast<int>(SkillPageNo::MAX)];
	GameEngineCollision* SkillPageCollider_[static_cast<int>(SkillPageNo::MAX)];

private: // ��ų�������� ���ϴ� ��ų ������ ����
	std::vector<MainPlayer_SkillIcon*> SkillPageToIcon[static_cast<int>(SkillPageNo::MAX)];

private:
	GameEngineUIRenderer* CloseButton_;							// ��ųâ �����ư ������
	GameEngineCollision* CloseButtonCollider_;					// ��ųâ �����ư �浹ü
	Button_State CloseButtonState_;								// ��ư ����

public:
	SkillView();
	~SkillView();

protected:		// delete constructer
	SkillView(const SkillView& _other) = delete;
	SkillView(SkillView&& _other) noexcept = delete;

private:		//delete operator
	SkillView& operator=(const SkillView& _other) = delete;
	SkillView& operator=(const SkillView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void InitSkillView();

public:
	void CloseButtonClick(GameEngineCollision* _Other);

public:
	void SkillPage1ChangeClick(GameEngineCollision* _Other);
	void SkillPage2ChangeClick(GameEngineCollision* _Other);
	void SkillPage3ChangeClick(GameEngineCollision* _Other);
	void SkillPageTabChange(SkillPageNo _SkillPageNo);
};


#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �з� : �÷��̾� UI
// �뵵 : ��ųâ
// ���� : ��ų������
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_SkillIcon;
class GameEngineLevel;
class SkillView : public GameEngineActor
{
private:
	static SkillPageNo CurSkillPage;
	static int SkillPoint;

private:	// member Var
	GameEngineUIRenderer* PanelRenderer_;						// ��ųâ �ǳ� ������
	GameEngineCollision* PanelCol_;								// ��ųâ �ǳ� �浹ü(�÷��̾� �̵��Ұ��Ǵ�)

private: // ��ų������
	GameEngineUIRenderer* SkillPagePanel_[static_cast<int>(SkillPageNo::MAX)];
	GameEngineCollision* SkillPageCollider_[static_cast<int>(SkillPageNo::MAX)];

private: // ��ų�������� ���ϴ� ��ų ������ ����
	std::vector<MainPlayer_SkillIcon*> SkillPageToIcon[static_cast<int>(SkillPageNo::MAX)];

private:
	GameEngineUIRenderer* CloseButton_;							// ��ųâ �����ư ������
	GameEngineCollision* CloseButtonCollider_;					// ��ųâ �����ư �浹ü
	Button_State CloseButtonState_;								// ��ư ����

private:
	GameEngineUIRenderer* SkillPointTitle_;
	GameEngineUIRenderer* CurSkillPoint_;
	GameEngineUIRenderer* Page1Name_;
	GameEngineUIRenderer* Page2Name_;
	GameEngineUIRenderer* Page3Name_;

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
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
	void InitSkillView();

public:
	void CloseButtonClick(GameEngineCollision* _Other);

public:
	void SkillPage1ChangeClick(GameEngineCollision* _Other);
	void SkillPage2ChangeClick(GameEngineCollision* _Other);
	void SkillPage3ChangeClick(GameEngineCollision* _Other);
	void SkillPageTabChange(SkillPageNo _SkillPageNo);

public:
	void SkillIconEnabled(bool _Flag);
	
public:
	void LevelUpSkillPointGrant();
	void SkillPointDeduction();
};


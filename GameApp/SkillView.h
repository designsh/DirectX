#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

struct SkillPage
{

};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_SkillPage;
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


private: // ��ų�������� ���ϴ� ��ų ������ ����



private:
	GameEngineUIRenderer* CloseButton_;							// ��ųâ �����ư ������
	GameEngineCollision* MainCollider_;							// ��ųâ �����ư �浹ü

private:
	Button_State ButtonState_;									// ��ư ����

private: // ��ų������ ����


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
};


#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// ��ų��ư ����
class GameEngineUIRenderer;
class GameEngineCollision;
struct SkillButton
{
	GameEngineUIRenderer*	ButtonRenderer_;		// ��ų��ư ������
	GameEngineCollision*	ButtonCollision_;		// ��ų��ư �浹ü

	bool					SkillActive_;			// ��ų Ȱ��ȭ ����(true : Ȱ��, false : ��Ȱ��)
													// Ȱ��ȭ �����̿��߸� ��ų ����������
	
	int						SkillCode_;				// ��ų�ڵ�(ID)
	std::string				SkillName_;				// ��ų��

	int						SkillPageRow_;			// ���� ��ų ������������ Row
	int						SkillPageColumn_;		// ���� ��ų ������������ Column
	float4					SkillPos_;				// ���� ��ų ������������ ��ġ

	int						CurSkillLevel_;			// ���� ��ų ����
};

// �з� : ��ųâ�� ������
// �뵵 : �������� ��ų����Ʈ ����
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_SkillPage : public GameEngineActor
{
private:	// member Var
	SkillPageNo PageNo_;

private:
	GameEngineUIRenderer* PagePanel_;


public:
	MainPlayer_SkillPage();
	~MainPlayer_SkillPage();

protected:		// delete constructer
	MainPlayer_SkillPage(const MainPlayer_SkillPage& _other) = delete;
	MainPlayer_SkillPage(MainPlayer_SkillPage&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_SkillPage& operator=(const MainPlayer_SkillPage& _other) = delete;
	MainPlayer_SkillPage& operator=(const MainPlayer_SkillPage&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


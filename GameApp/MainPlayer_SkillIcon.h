#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �з� : ��ųâ �������� ���� ��ų������
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_SkillIcon : public GameEngineActor
{
private:	// member Var
	SkillPageNo PageNo_;

private:
	std::string				SkillName_;				// ��ų��
	int						SkillCode_;				// ��ų�ڵ�(ID)
	bool					SkillActive_;			// ��ų Ȱ��ȭ ����(true : Ȱ��, false : ��Ȱ��)

	int						SkillPageRow_;			// ���� ��ų ������������ Row
	int						SkillPageColumn_;		// ���� ��ų ������������ Column
	float4					SkillPos_;				// ���� ��ų ������������ ��ġ

	int						CurSkillLevel_;			// ���� ��ų ����

private:
	GameEngineUIRenderer*	IconRenderer_;			// ��ų ������ ������
	GameEngineCollision*	IconCollision_;			// ��ų ������ �浹ü
	GameEngineUIRenderer*	CurLevelRenderer_;		// ��ų ���� ���� ������

private:
	Button_State ButtonState_;

public:
	MainPlayer_SkillIcon();
	~MainPlayer_SkillIcon();

protected:		// delete constructer
	MainPlayer_SkillIcon(const MainPlayer_SkillIcon& _other) = delete;
	MainPlayer_SkillIcon(MainPlayer_SkillIcon&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_SkillIcon& operator=(const MainPlayer_SkillIcon& _other) = delete;
	MainPlayer_SkillIcon& operator=(const MainPlayer_SkillIcon&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void SkillIconClick(GameEngineCollision* _Other);
	void SkillLevelUp();

public:
	void CreateSkillIcon(SkillPageNo _PageNo, const std::string& _SkillName, int _SkillCode, bool _SkillActiveFlag, int _Row, int _Column, int _CurSkillLevel);

public:
	void SetSkillIconActive();
	void SetSkillIconInactvie();
};


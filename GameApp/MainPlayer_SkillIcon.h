#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 분류 : 스킬창 페이지의 속한 스킬아이콘
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_SkillIcon : public GameEngineActor
{
private:	// member Var
	SkillPageNo PageNo_;

private:
	std::string				SkillName_;				// 스킬명
	int						SkillCode_;				// 스킬코드(ID)
	bool					SkillActive_;			// 스킬 활성화 여부(true : 활성, false : 비활성)

	int						SkillPageRow_;			// 속한 스킬 페이지에서의 Row
	int						SkillPageColumn_;		// 속한 스킬 페이지에서의 Column
	float4					SkillPos_;				// 속한 스킬 페이지에서이 위치

	int						CurSkillLevel_;			// 현재 스킬 레벨

private:
	GameEngineUIRenderer*	IconRenderer_;			// 스킬 아이콘 렌더러
	GameEngineCollision*	IconCollision_;			// 스킬 아이콘 충돌체
	GameEngineUIRenderer*	CurLevelRenderer_;		// 스킬 현재 레벨 렌더러

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


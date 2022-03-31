#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 스킬버튼 정보
class GameEngineUIRenderer;
class GameEngineCollision;
struct SkillButton
{
	GameEngineUIRenderer*	ButtonRenderer_;		// 스킬버튼 렌더러
	GameEngineCollision*	ButtonCollision_;		// 스킬버튼 충돌체

	bool					SkillActive_;			// 스킬 활성화 여부(true : 활성, false : 비활성)
													// 활성화 상태이여야만 스킬 레벨업가능
	
	int						SkillCode_;				// 스킬코드(ID)
	std::string				SkillName_;				// 스킬명

	int						SkillPageRow_;			// 속한 스킬 페이지에서의 Row
	int						SkillPageColumn_;		// 속한 스킬 페이지에서의 Column
	float4					SkillPos_;				// 속한 스킬 페이지에서이 위치

	int						CurSkillLevel_;			// 현재 스킬 레벨
};

// 분류 : 스킬창의 페이지
// 용도 : 페이지별 스킬리스트 관리
// 설명 : 
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


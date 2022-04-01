#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

struct SkillPage
{

};

// 분류 : 
// 용도 : 
// 설명 : 
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
	GameEngineUIRenderer* PanelRenderer_;						// 스킬창 판넬 렌더러

private: // 스킬페이지


private: // 스킬페이지에 속하는 스킬 아이콘 정보



private:
	GameEngineUIRenderer* CloseButton_;							// 스킬창 종료버튼 렌더러
	GameEngineCollision* MainCollider_;							// 스킬창 종료버튼 충돌체

private:
	Button_State ButtonState_;									// 버튼 상태

private: // 스킬페이지 관련


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


#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 분류 : 플레이어 UI
// 용도 : 스킬창
// 설명 : 스킬레벨업
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
	GameEngineUIRenderer* PanelRenderer_;						// 스킬창 판넬 렌더러

private: // 스킬페이지
	GameEngineUIRenderer* SkillPagePanel_[static_cast<int>(SkillPageNo::MAX)];
	GameEngineCollision* SkillPageCollider_[static_cast<int>(SkillPageNo::MAX)];

private: // 스킬페이지에 속하는 스킬 아이콘 정보
	std::vector<MainPlayer_SkillIcon*> SkillPageToIcon[static_cast<int>(SkillPageNo::MAX)];

private:
	GameEngineUIRenderer* CloseButton_;							// 스킬창 종료버튼 렌더러
	GameEngineCollision* CloseButtonCollider_;					// 스킬창 종료버튼 충돌체
	Button_State CloseButtonState_;								// 버튼 상태

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


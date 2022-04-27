#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 분류 : 플레이어 UI
// 용도 : 스킬창
// 설명 : 스킬레벨업
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
	GameEngineUIRenderer* PanelRenderer_;						// 스킬창 판넬 렌더러
	GameEngineCollision* PanelCol_;								// 스킬창 판넬 충돌체(플레이어 이동불가판단)

private: // 스킬페이지
	GameEngineUIRenderer* SkillPagePanel_[static_cast<int>(SkillPageNo::MAX)];
	GameEngineCollision* SkillPageCollider_[static_cast<int>(SkillPageNo::MAX)];

private: // 스킬페이지에 속하는 스킬 아이콘 정보
	std::vector<MainPlayer_SkillIcon*> SkillPageToIcon[static_cast<int>(SkillPageNo::MAX)];

private:
	GameEngineUIRenderer* CloseButton_;							// 스킬창 종료버튼 렌더러
	GameEngineCollision* CloseButtonCollider_;					// 스킬창 종료버튼 충돌체
	Button_State CloseButtonState_;								// 버튼 상태

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


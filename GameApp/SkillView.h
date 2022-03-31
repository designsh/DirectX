#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class SkillView : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* PanelRenderer_;						// 스킬창 판넬 렌더러

private:
	GameEngineUIRenderer* CloseButton_;							// 스킬창 종료버튼 렌더러
	GameEngineCollision* MainCollider_;							// 스킬창 종료버튼 충돌체

private:
	Button_State ButtonState_;									// 버튼 상태

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
};


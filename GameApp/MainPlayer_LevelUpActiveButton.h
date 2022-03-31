#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

enum class LevelUpPointType
{
	NONE = -1,
	STAT,
	SKILL,
	MAX
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_LevelUpActiveButton : public GameEngineActor
{
private:	// member Var
	bool IsPointExhaust_;						// 포인트 소진시 False, 레벨업시 true
	LevelUpPointType LevelUpPointType_;			// 스탯/스킬 포인트 판단 타입
	Button_State ButtonState_;					// 버튼 상태

private:
	GameEngineUIRenderer* Button_;				// 
	GameEngineCollision* ButtonCollision_;		// 

public:
	MainPlayer_LevelUpActiveButton();
	~MainPlayer_LevelUpActiveButton();

protected:		// delete constructer
	MainPlayer_LevelUpActiveButton(const MainPlayer_LevelUpActiveButton& _other) = delete;
	MainPlayer_LevelUpActiveButton(MainPlayer_LevelUpActiveButton&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_LevelUpActiveButton& operator=(const MainPlayer_LevelUpActiveButton& _other) = delete;
	MainPlayer_LevelUpActiveButton& operator=(const MainPlayer_LevelUpActiveButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetLevelUpActiveButtonInfo(LevelUpPointType _Type, const float4& _Pos);

public:
	void ButtonClick(GameEngineCollision* _Other);
	void ButtonTypeProcess();
	
public:
	void LevelUpPointButtonActive();
	void LevelUpPointExhaust();
};


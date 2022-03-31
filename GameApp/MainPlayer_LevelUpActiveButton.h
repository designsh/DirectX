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

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_LevelUpActiveButton : public GameEngineActor
{
private:	// member Var
	bool IsPointExhaust_;						// ����Ʈ ������ False, �������� true
	LevelUpPointType LevelUpPointType_;			// ����/��ų ����Ʈ �Ǵ� Ÿ��
	Button_State ButtonState_;					// ��ư ����

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


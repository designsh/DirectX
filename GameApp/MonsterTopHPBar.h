#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineProgressBarRenderer;
class GameEngineUIRenderer;
class MonsterTopHPBar : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* CurSelMonsterName_;
	GameEngineProgressBarRenderer* HPBar_;

private:
	std::string CurMonsterName_;
	float CurHP_;
	float MapHP_;
	float4 TextColor_;

public:
	MonsterTopHPBar();
	~MonsterTopHPBar();

protected:		// delete constructer
	MonsterTopHPBar(const MonsterTopHPBar& _other) = delete;
	MonsterTopHPBar(MonsterTopHPBar&& _other) noexcept = delete;

private:		//delete operator
	MonsterTopHPBar& operator=(const MonsterTopHPBar& _other) = delete;
	MonsterTopHPBar& operator=(const MonsterTopHPBar&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetCurMonster(const std::string& _MonsterName, int _MaxHP, int _HP, const float4& _TextColor = float4::WHITE);
	void CurMonsterTopHPBarOff();

};


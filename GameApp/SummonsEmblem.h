#pragma once
#include <GameEngine/GameEngineActor.h>

#include "SummonsGolem.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class SummonsEmblem : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* GolemEmblem_;
	GameEngineUIRenderer* SketelonWarriorEmblem_;
	GameEngineUIRenderer* SketelonWizardEmblem_;

private:
	int WarriorCnt_;
	int WizardCnt_;

private:
	GolemType CurGolemType_;

public:
	SummonsEmblem();
	~SummonsEmblem();

protected:		// delete constructer
	SummonsEmblem(const SummonsEmblem& _other) = delete;
	SummonsEmblem(SummonsEmblem&& _other) noexcept = delete;

private:		//delete operator
	SummonsEmblem& operator=(const SummonsEmblem& _other) = delete;
	SummonsEmblem& operator=(const SummonsEmblem&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
	void GolemEmblemUpdate(GolemType _SpawnGolemType);
	void SketelonWarriorUpdate(int _CurCount);
	void SketelonWizardUpdate(int _CurCount);
};


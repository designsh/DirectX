#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 캐릭터선택 화면
// 용도 : 
// 설명 : 
class SelectCharactorLevel : public GameEngineLevel
{
private:	// member Var

public:
	SelectCharactorLevel();
	~SelectCharactorLevel();

protected:		// delete constructer
	SelectCharactorLevel(const SelectCharactorLevel& _other) = delete;
	SelectCharactorLevel(SelectCharactorLevel&& _other) noexcept = delete;

private:		//delete operator
	SelectCharactorLevel& operator=(const SelectCharactorLevel& _other) = delete;
	SelectCharactorLevel& operator=(const SelectCharactorLevel&& _other) = delete;

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};


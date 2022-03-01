#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 캐릭터선택 화면
// 용도 : 
// 설명 : 
class SelectCharacterLevel : public GameEngineLevel
{
private:	// member Var

public:
	SelectCharacterLevel();
	~SelectCharacterLevel();

protected:		// delete constructer
	SelectCharacterLevel(const SelectCharacterLevel& _other) = delete;
	SelectCharacterLevel(SelectCharacterLevel&& _other) noexcept = delete;

private:		//delete operator
	SelectCharacterLevel& operator=(const SelectCharacterLevel& _other) = delete;
	SelectCharacterLevel& operator=(const SelectCharacterLevel&& _other) = delete;

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};


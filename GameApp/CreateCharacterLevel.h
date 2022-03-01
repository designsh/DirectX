#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 캐릭터생성화면
// 용도 : 
// 설명 : 
class CreateCharacterLevel : public GameEngineLevel
{
private:	// member Var

public:
	CreateCharacterLevel();
	~CreateCharacterLevel();

protected:		// delete constructer
	CreateCharacterLevel(const CreateCharacterLevel& _other) = delete;
	CreateCharacterLevel(CreateCharacterLevel&& _other) noexcept = delete;

private:		//delete operator
	CreateCharacterLevel& operator=(const CreateCharacterLevel& _other) = delete;
	CreateCharacterLevel& operator=(const CreateCharacterLevel&& _other) = delete;

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};


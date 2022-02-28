#pragma once
#include <GameEngine/GameEngineLevel.h>

// �з� : ĳ���ͻ���ȭ��
// �뵵 : 
// ���� : 
class CreateCharactorLevel : public GameEngineLevel
{
private:	// member Var

public:
	CreateCharactorLevel();
	~CreateCharactorLevel();

protected:		// delete constructer
	CreateCharactorLevel(const CreateCharactorLevel& _other) = delete;
	CreateCharactorLevel(CreateCharactorLevel&& _other) noexcept = delete;

private:		//delete operator
	CreateCharactorLevel& operator=(const CreateCharactorLevel& _other) = delete;
	CreateCharactorLevel& operator=(const CreateCharactorLevel&& _other) = delete;

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};


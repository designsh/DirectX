#pragma once
#include <GameEngine/GameEngineLevel.h>

// �з� : ĳ���ͼ��� ȭ��
// �뵵 : 
// ���� : 
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


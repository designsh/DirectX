#pragma once
#include <GameEngine/GameEngineLevel.h>

// �з� : ī�������� ȭ��
// �뵵 : 
// ���� : 
class MainPlayer;
class ChaosSanctuaryLevel : public GameEngineLevel
{
private:	// member Var
	MainPlayer* MainPlayer_;

public:
	ChaosSanctuaryLevel();
	~ChaosSanctuaryLevel();

protected:		// delete constructer
	ChaosSanctuaryLevel(const ChaosSanctuaryLevel& _other) = delete;
	ChaosSanctuaryLevel(ChaosSanctuaryLevel&& _other) noexcept = delete;

private:		//delete operator
	ChaosSanctuaryLevel& operator=(const ChaosSanctuaryLevel& _other) = delete;
	ChaosSanctuaryLevel& operator=(const ChaosSanctuaryLevel&& _other) = delete;

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};


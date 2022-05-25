#pragma once
#include <GameEngine/GameEngineLevel.h>

// �з� : ���� ȭ��
// �뵵 : 
// ���� : 
class EndingBackDrop;
class EndingCredit;
class EndingLevel : public GameEngineLevel
{
private:
	static bool ResourceLoadEndCheck;

private:	// member Var
	EndingBackDrop* BackDrop_;
	EndingCredit* Credit_;

public:
	EndingLevel();
	~EndingLevel();

protected:		// delete constructer
	EndingLevel(const EndingLevel& _other) = delete;
	EndingLevel(EndingLevel&& _other) noexcept = delete;

private:		//delete operator
	EndingLevel& operator=(const EndingLevel& _other) = delete;
	EndingLevel& operator=(const EndingLevel&& _other) = delete;

public:
	virtual void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	virtual void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;

private:
	void CreateLevelActor();
};


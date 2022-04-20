#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 캐릭터생성화면
// 용도 : 
// 설명 : 
class CreateCharacterInputText;
class CurPlayerGameStartButton;
class TitleLevelMoveBtn;
class ClassSelectObject;
class CreateCharacterLevel : public GameEngineLevel
{
private:
	static bool ResourceLoadEndCheck;

private:	// member Var
	CreateCharacterInputText* IDInputTextBox_;
	CurPlayerGameStartButton* GameStartBtn_;
	TitleLevelMoveBtn* PrevMenuBtn_;
	ClassSelectObject* NecromancerClass_;

public:
	CreateCharacterLevel();
	~CreateCharacterLevel();

protected:		// delete constructer
	CreateCharacterLevel(const CreateCharacterLevel& _other) = delete;
	CreateCharacterLevel(CreateCharacterLevel&& _other) noexcept = delete;

private:		//delete operator
	CreateCharacterLevel& operator=(const CreateCharacterLevel& _other) = delete;
	CreateCharacterLevel& operator=(const CreateCharacterLevel&& _other) = delete;

private:
	void CreateLevelActor();

public: 
	void ClassImageCutting();

public:
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;
	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
};


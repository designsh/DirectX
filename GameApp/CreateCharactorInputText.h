#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 캐릭터생성레벨 ID입력창
// 설명 : 
class CreateCharactorInputText : public GameEngineActor
{
private:	// member Var

public:
	CreateCharactorInputText();
	~CreateCharactorInputText();

protected:		// delete constructer
	CreateCharactorInputText(const CreateCharactorInputText& _other) = delete;
	CreateCharactorInputText(CreateCharactorInputText&& _other) noexcept = delete;

private:		//delete operator
	CreateCharactorInputText& operator=(const CreateCharactorInputText& _other) = delete;
	CreateCharactorInputText& operator=(const CreateCharactorInputText&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


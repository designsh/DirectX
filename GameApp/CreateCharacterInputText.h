#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 캐릭터생성레벨 ID입력창
// 설명 : 
class CreateCharacterInputText : public GameEngineActor
{
private:	// member Var

public:
	CreateCharacterInputText();
	~CreateCharacterInputText();

protected:		// delete constructer
	CreateCharacterInputText(const CreateCharacterInputText& _other) = delete;
	CreateCharacterInputText(CreateCharacterInputText&& _other) noexcept = delete;

private:		//delete operator
	CreateCharacterInputText& operator=(const CreateCharacterInputText& _other) = delete;
	CreateCharacterInputText& operator=(const CreateCharacterInputText&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 캐릭터선택레벨 버튼
// 설명 : 캐랙터생성레벨 이동
class CreateCharacterButton : public GameEngineActor
{
private:	// member Var

public:
	CreateCharacterButton();
	~CreateCharacterButton();

protected:		// delete constructer
	CreateCharacterButton(const CreateCharacterButton& _other) = delete;
	CreateCharacterButton(CreateCharacterButton&& _other) noexcept = delete;

private:		//delete operator
	CreateCharacterButton& operator=(const CreateCharacterButton& _other) = delete;
	CreateCharacterButton& operator=(const CreateCharacterButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


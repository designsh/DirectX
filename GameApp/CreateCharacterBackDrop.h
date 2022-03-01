#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 이미지
// 용도 : 캐릭터생성레벨 배경
// 설명 : 
class GameEngineImageRenderer;
class CreateCharacterBackDrop : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* BackDrop_;

public:
	CreateCharacterBackDrop();
	~CreateCharacterBackDrop();

protected:		// delete constructer
	CreateCharacterBackDrop(const CreateCharacterBackDrop& _other) = delete;
	CreateCharacterBackDrop(CreateCharacterBackDrop&& _other) noexcept = delete;

private:		//delete operator
	CreateCharacterBackDrop& operator=(const CreateCharacterBackDrop& _other) = delete;
	CreateCharacterBackDrop& operator=(const CreateCharacterBackDrop&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


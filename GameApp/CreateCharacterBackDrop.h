#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �̹���
// �뵵 : ĳ���ͻ������� ���
// ���� : 
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


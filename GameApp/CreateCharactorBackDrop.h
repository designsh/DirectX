#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �̹���
// �뵵 : ĳ���ͻ������� ���
// ���� : 
class GameEngineImageRenderer;
class CreateCharactorBackDrop : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* BackDrop_;

public:
	CreateCharactorBackDrop();
	~CreateCharactorBackDrop();

protected:		// delete constructer
	CreateCharactorBackDrop(const CreateCharactorBackDrop& _other) = delete;
	CreateCharactorBackDrop(CreateCharactorBackDrop&& _other) noexcept = delete;

private:		//delete operator
	CreateCharactorBackDrop& operator=(const CreateCharactorBackDrop& _other) = delete;
	CreateCharactorBackDrop& operator=(const CreateCharactorBackDrop&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


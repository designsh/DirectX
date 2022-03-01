#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �ִϸ��̼�
// �뵵 : ĳ���ͻ������� ķ�����̾�
// ���� : 
class CreateCharacterFireObject : public GameEngineActor
{
private:	// member Var

public:
	CreateCharacterFireObject();
	~CreateCharacterFireObject();

protected:		// delete constructer
	CreateCharacterFireObject(const CreateCharacterFireObject& _other) = delete;
	CreateCharacterFireObject(CreateCharacterFireObject&& _other) noexcept = delete;

private:		//delete operator
	CreateCharacterFireObject& operator=(const CreateCharacterFireObject& _other) = delete;
	CreateCharacterFireObject& operator=(const CreateCharacterFireObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


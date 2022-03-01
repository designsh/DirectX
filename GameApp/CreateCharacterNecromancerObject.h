#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �ִϸ��̼�
// �뵵 : ĳ���ͻ������� ��ũ�θǼ�ĳ����
// ���� : 
class CreateCharacterNecromancerObject : public GameEngineActor
{
private:	// member Var

public:
	CreateCharacterNecromancerObject();
	~CreateCharacterNecromancerObject();

protected:		// delete constructer
	CreateCharacterNecromancerObject(const CreateCharacterNecromancerObject& _other) = delete;
	CreateCharacterNecromancerObject(CreateCharacterNecromancerObject&& _other) noexcept = delete;

private:		//delete operator
	CreateCharacterNecromancerObject& operator=(const CreateCharacterNecromancerObject& _other) = delete;
	CreateCharacterNecromancerObject& operator=(const CreateCharacterNecromancerObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


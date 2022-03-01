#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �ִϸ��̼�
// �뵵 : ĳ���ͻ������� ��ũ�θǼ�ĳ����
// ���� : 
class CreateCharactorNecromancerObject : public GameEngineActor
{
private:	// member Var

public:
	CreateCharactorNecromancerObject();
	~CreateCharactorNecromancerObject();

protected:		// delete constructer
	CreateCharactorNecromancerObject(const CreateCharactorNecromancerObject& _other) = delete;
	CreateCharactorNecromancerObject(CreateCharactorNecromancerObject&& _other) noexcept = delete;

private:		//delete operator
	CreateCharactorNecromancerObject& operator=(const CreateCharactorNecromancerObject& _other) = delete;
	CreateCharactorNecromancerObject& operator=(const CreateCharactorNecromancerObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


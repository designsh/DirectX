#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �ִϸ��̼�
// �뵵 : ĳ���ͻ������� ķ�����̾�
// ���� : 
class CreateCharactorFireObject : public GameEngineActor
{
private:	// member Var

public:
	CreateCharactorFireObject();
	~CreateCharactorFireObject();

protected:		// delete constructer
	CreateCharactorFireObject(const CreateCharactorFireObject& _other) = delete;
	CreateCharactorFireObject(CreateCharactorFireObject&& _other) noexcept = delete;

private:		//delete operator
	CreateCharactorFireObject& operator=(const CreateCharactorFireObject& _other) = delete;
	CreateCharactorFireObject& operator=(const CreateCharactorFireObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


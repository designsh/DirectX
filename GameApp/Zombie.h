#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : �����¿��� ���������� ��ȯ�̵��ϴٰ� �÷��̾� �߽߰� �÷��̾�Է� �̵��ϸ�,
//           �÷��̾ ���ݹ����� �����ϸ� ���������� ���Ѵ�.
class GameEngineImageRenderer;
class Zombie : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Zombie_;

public:
	Zombie();
	~Zombie();

protected:		// delete constructer
	Zombie(const Zombie& _other) = delete;
	Zombie(Zombie&& _other) noexcept = delete;

private:		//delete operator
	Zombie& operator=(const Zombie& _other) = delete;
	Zombie& operator=(const Zombie&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


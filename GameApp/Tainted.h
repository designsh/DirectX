#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : �����¿��� ���������� ��ȯ�̵��ϴٰ� �÷��̾� �߽߰� �÷��̾�Է� �̵��ϸ�,
//           �÷��̾ ���ݹ����� �����ϸ� ����ü�� �߻��Ͽ� �÷��̾�� ������ ���ϰų�, ���������� ���Ѵ�.
class GameEngineImageRenderer;
class Tainted : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Tainted_;

private: // ���� ����
	bool SpecialAttack_;		// ����ü ���� ����(�⺻ : ��������)

public:
	Tainted();
	~Tainted();

protected:		// delete constructer
	Tainted(const Tainted& _other) = delete;
	Tainted(Tainted&& _other) noexcept = delete;

private:		//delete operator
	Tainted& operator=(const Tainted& _other) = delete;
	Tainted& operator=(const Tainted&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


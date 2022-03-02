#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : �����¿��� ���������� ��ȯ�̵��ϴٰ� �÷��̾� �߽߰� �÷��̾�Է� �̵��ϸ�,
//           �÷��̾�� ������ ���Ѵ�.
class GameEngineImageRenderer;
class Fallen : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Fallen_;

private: // ���� ����


public:
	Fallen();
	~Fallen();

protected:		// delete constructer
	Fallen(const Fallen& _other) = delete;
	Fallen(Fallen&& _other) noexcept = delete;

private:		//delete operator
	Fallen& operator=(const Fallen& _other) = delete;
	Fallen& operator=(const Fallen&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


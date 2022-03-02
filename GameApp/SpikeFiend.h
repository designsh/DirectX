#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �Ϲݸ���
// �뵵 : 
// ���� : �����¿��� ���������� ��ȯ�̵��ϴٰ� �÷��̾� �߽߰� �÷��̾�Է� �̵��ϸ�,
//           �÷��̾ ���ݹ����� �����ϸ� ����ü�� �߻��Ͽ� �÷��̾�� ������ ���Ѵ�.
class GameEngineImageRenderer;
class SpikeFiend : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* SpikeFiend_;

private: // ���� ����


public:
	SpikeFiend();
	~SpikeFiend();

protected:		// delete constructer
	SpikeFiend(const SpikeFiend& _other) = delete;
	SpikeFiend(SpikeFiend&& _other) noexcept = delete;

private:		//delete operator
	SpikeFiend& operator=(const SpikeFiend& _other) = delete;
	SpikeFiend& operator=(const SpikeFiend&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


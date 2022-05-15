#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ��������
// �뵵 : īŸ�޷����� ��������
// ���� : �ʵ�(��ü��)���� �÷��̾ ���� ������ ���� ��ġ�� ���� �� ��ġ�� �����ϴ� �濡 �����ϸ�,
//            �Ϲݰ���(��������)�� ��ų����(���Ÿ�) ������ ������.
//            �� 1������ �ʵ忡 �����ϸ�, ����� ��� ����Ʈ(ī�޶� ����ŷ, �Ҳɿ�����Ʈ ��ȯ ��)�� �����ϸ�,
//            �������Ʈ ����� Boss Portal(Auto)�� �����Ͽ� �÷��̾ ���� ������ ������ �� �ְ� �����Ѵ�.
//            �������Ʈ�� ���ÿ� �뷮�� ������ or ��带 ����Ѵ�.
class GameEngineImageRenderer;
class GameEngineCollision;
class Andariel : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Andariel_;
	GameEngineCollision* BodyCollider_;
	GameEngineCollision* AttackCollider_;

private:
	std::list<PathIndex> MovePath_;

public:
	Andariel();
	~Andariel();

protected:		// delete constructer
	Andariel(const Andariel& _other) = delete;
	Andariel(Andariel&& _other) noexcept = delete;

private:		//delete operator
	Andariel& operator=(const Andariel& _other) = delete;
	Andariel& operator=(const Andariel&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


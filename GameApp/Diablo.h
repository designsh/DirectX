#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ��������
// �뵵 : ī�������������� ��������
// ���� : �ʵ�(��ü��)���� �÷��̾ ���� ������ ���� ��ġ�� ���� �� ��ġ�� �����ϴ� �濡 �����ϸ�,
//            �Ϲݰ���(��������)�� ��ų����(���Ÿ�) ������ ������.
//            �� 1������ �ʵ忡 �����ϸ�, ����� ��� ����Ʈ(ī�޶� ����ŷ, �Ҳɿ�����Ʈ ��ȯ ��)�� �����ϸ�,
//            �������Ʈ ����� Boss Portal(Auto)�� �����Ͽ� �÷��̾ ���� ������ ������ �� �ְ� �����Ѵ�.
//            �������Ʈ�� ���ÿ� �뷮�� ������ or ��带 ����Ѵ�.
class GameEngineImageRenderer;
class Diablo : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Diablo_;

public:
	Diablo();
	~Diablo();

protected:		// delete constructer
	Diablo(const Diablo& _other) = delete;
	Diablo(Diablo&& _other) noexcept = delete;

private:		//delete operator
	Diablo& operator=(const Diablo& _other) = delete;
	Diablo& operator=(const Diablo&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


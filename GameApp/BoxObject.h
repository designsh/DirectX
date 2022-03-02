#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �ڽ�
// �뵵 : ������ ��� or ��� ���
// ���� : �ʿ� �������� ��ġ�Ǹ�, Ÿ�Կ����� �ؽ��İ� �����ȴ�.
//            ����, ���콺�� �浹�Ͽ� �÷��̾ �����Ÿ� ���Խ� �ִϸ��̼��� ���۵Ǹ� �ִϸ��̼� ������ �������� �Ǹ�
//            �������� ������ or ��� ����ȴ�.
class GameEngineImageRenderer;
class BoxObject : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* BoxObject_;

private:
	int BoxType_;
	bool AnimationStart_;

public:
	BoxObject();
	~BoxObject();

protected:		// delete constructer
	BoxObject(const BoxObject& _other) = delete;
	BoxObject(BoxObject&& _other) noexcept = delete;

private:		//delete operator
	BoxObject& operator=(const BoxObject& _other) = delete;
	BoxObject& operator=(const BoxObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetBoxType(int _BoxType);
};


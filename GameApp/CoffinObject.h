#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ��
// �뵵 : ������ ��� or ��� ��� or ���� ��ȯ
// ���� : �ʿ� �������� ��ġ�Ǹ�, Ÿ�Կ����� �ؽ��İ� �����ȴ�.
//            ����, ���콺�� �浹�Ͽ� �÷��̾ �����Ÿ� ���Խ� �ִϸ��̼��� ���۵Ǹ� �ִϸ��̼� ������ �������� �Ǹ�
//            �������� ������ or ��� ����ǰų�, ���Ͱ� ��ȯ�ȴ�.
//            �̶� ��ȯ�ϴ� ���ʹ� Zombie�� ����
class GameEngineImageRenderer;
class CoffinObject : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Coffin_;

private:
	int CoffinType_; // 1 ~ 6�� Ÿ���� �����ϸ� �ش� Ÿ�Կ� ���� �ؽ��İ� ����
	bool AnimationStart_;

public:
	CoffinObject();
	~CoffinObject();

protected:		// delete constructer
	CoffinObject(const CoffinObject& _other) = delete;
	CoffinObject(CoffinObject&& _other) noexcept = delete;

private:		//delete operator
	CoffinObject& operator=(const CoffinObject& _other) = delete;
	CoffinObject& operator=(const CoffinObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetCoffinType(int _CoffinType);
};


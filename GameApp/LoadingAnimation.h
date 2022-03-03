#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �ִϸ��̼�
// �뵵 : �ε�
// ���� : �÷��̾�����, ������, ��������, ������Ʈ���� �� ��� ������ �ε��� �� �÷��̷����� �̵�
class GameEngineImageRenderer;
class LoadingAnimation : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* LoadingAnimation_;

	int test;

public:
	LoadingAnimation();
	~LoadingAnimation();

protected:		// delete constructer
	LoadingAnimation(const LoadingAnimation& _other) = delete;
	LoadingAnimation(LoadingAnimation&& _other) noexcept = delete;

private:		//delete operator
	LoadingAnimation& operator=(const LoadingAnimation& _other) = delete;
	LoadingAnimation& operator=(const LoadingAnimation&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void LoadingEnd();

	void TestFunction();
};


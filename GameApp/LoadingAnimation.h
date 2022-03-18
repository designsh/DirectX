#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �ִϸ��̼�
// �뵵 : �ε�
// ���� : �÷��̾�����, ������, ��������, ������Ʈ���� �� ��� ������ �ε��� �� �÷��̷����� �̵�
class GameEngineUIRenderer;
class LoadingAnimation : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* LoadingAnimation_;

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
};


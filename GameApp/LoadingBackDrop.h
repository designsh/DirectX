#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �̹���
// �뵵 : �ε����� ���
// ���� : 
class GameEngineImageRenderer;
class LoadingBackDrop : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* BackDrop_;

public:
	LoadingBackDrop();
	~LoadingBackDrop();

protected:		// delete constructer
	LoadingBackDrop(const LoadingBackDrop& _other) = delete;
	LoadingBackDrop(LoadingBackDrop&& _other) noexcept = delete;

private:		//delete operator
	LoadingBackDrop& operator=(const LoadingBackDrop& _other) = delete;
	LoadingBackDrop& operator=(const LoadingBackDrop&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


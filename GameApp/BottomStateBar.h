#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �̹���
// �뵵 : �ϴܻ��¹�
// ���� : �÷��̾��� �ϴܻ��¹ٰ���
class GameEngineUIRenderer;
class BottomStateBar : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* BottomStateBar_;

public:
	BottomStateBar();
	~BottomStateBar();

protected:		// delete constructer
	BottomStateBar(const BottomStateBar& _other) = delete;
	BottomStateBar(BottomStateBar&& _other) noexcept = delete;

private:		//delete operator
	BottomStateBar& operator=(const BottomStateBar& _other) = delete;
	BottomStateBar& operator=(const BottomStateBar&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : ĳ���ͼ��÷��� ��ư
// ���� : ���õ� �÷��̾�� ���ӽ���
class SelPlayerGameStartButton : public GameEngineActor
{
private:	// member Var

public:
	SelPlayerGameStartButton();
	~SelPlayerGameStartButton();

protected:		// delete constructer
	SelPlayerGameStartButton(const SelPlayerGameStartButton& _other) = delete;
	SelPlayerGameStartButton(SelPlayerGameStartButton&& _other) noexcept = delete;

private:		//delete operator
	SelPlayerGameStartButton& operator=(const SelPlayerGameStartButton& _other) = delete;
	SelPlayerGameStartButton& operator=(const SelPlayerGameStartButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : ĳ���ͻ������� ��ư
// ���� : ���� ������ �÷��̾�� ���ӽ���
class CurPlayerGameStartButton : public GameEngineActor
{
private:	// member Var

public:
	CurPlayerGameStartButton();
	~CurPlayerGameStartButton();

protected:		// delete constructer
	CurPlayerGameStartButton(const CurPlayerGameStartButton& _other) = delete;
	CurPlayerGameStartButton(CurPlayerGameStartButton&& _other) noexcept = delete;

private:		//delete operator
	CurPlayerGameStartButton& operator=(const CurPlayerGameStartButton& _other) = delete;
	CurPlayerGameStartButton& operator=(const CurPlayerGameStartButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


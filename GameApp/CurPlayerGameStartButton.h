#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : ĳ���ͻ������� ��ư
// ���� : ���� ������ �÷��̾�� ���ӽ����ϸ�, �ʱ� ȭ�鿡 �����������ʴٰ� ����ڰ� ������ �����ϸ� ������
class GameEngineUIRenderer;
class GameEngineCollision;
class CurPlayerGameStartButton : public GameEngineActor
{
private:
	static bool ClassSelect_;

public:
	static void UserClassSelect();
	static void UserClassDeselect();

private:	// member Var
	GameEngineUIRenderer* CurPlayerGameStartBtn_;

private:
	bool RenderFlag_;

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
	void CheckSameID();
	bool DefaultPathFileNameCheck(const std::string& _PlayerID);
	void CreateCurPlayer(const std::string& _PlayerID);
};


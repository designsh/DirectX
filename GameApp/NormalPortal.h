#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ��Ż
// �뵵 : �Ϲ���Ż(�÷��̾��� ��Ż��ũ�� ������ ����޾� ��ȯ)
// ���� : �������� ������ �Ϲݹ濡�� ������ ��ȯ�ϴ� ��Ż ������ �����Ǵ� ����
class GameEngineImageRenderer;
class NormalPortal : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Portal_;

public:
	NormalPortal();
	~NormalPortal();

protected:		// delete constructer
	NormalPortal(const NormalPortal& _other) = delete;
	NormalPortal(NormalPortal&& _other) noexcept = delete;

private:		//delete operator
	NormalPortal& operator=(const NormalPortal& _other) = delete;
	NormalPortal& operator=(const NormalPortal&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


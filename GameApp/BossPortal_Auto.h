#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ��Ż
// �뵵 : ���������̵�
// ���� : �� ����(�ʵ巹��)���� ���� óġ�� �ڵ����� �����Ǵ� ��Ż
class GameEngineImageRenderer;
class BossPortal_Auto : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Portal_;

public:
	BossPortal_Auto();
	~BossPortal_Auto();

protected:		// delete constructer
	BossPortal_Auto(const BossPortal_Auto& _other) = delete;
	BossPortal_Auto(BossPortal_Auto&& _other) noexcept = delete;

private:		//delete operator
	BossPortal_Auto& operator=(const BossPortal_Auto& _other) = delete;
	BossPortal_Auto& operator=(const BossPortal_Auto&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


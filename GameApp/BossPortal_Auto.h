#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 포탈
// 용도 : 다음레벨이동
// 설명 : 각 레벨(필드레벨)에서 보스 처치시 자동으로 생성되는 포탈
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


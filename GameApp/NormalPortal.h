#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 포탈
// 용도 : 일반포탈(플레이어의 포탈스크롤 개수에 영향받아 소환)
// 설명 : 보스방을 제외한 일반방에서 마을로 귀환하는 포탈 생성시 생성되는 액터
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


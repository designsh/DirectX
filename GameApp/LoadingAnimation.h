#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 애니메이션
// 용도 : 로딩
// 설명 : 플레이어정보, 맵정보, 몬스터정보, 오브젝트정보 등 모든 정보를 로드한 뒤 플레이레벨로 이동
class GameEngineImageRenderer;
class LoadingAnimation : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* LoadingAnimation_;

	int test;

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

	void TestFunction();
};


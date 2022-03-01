#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 플레이어
// 용도 : 
// 설명 : 직업에 따라 정보가 다름
class CommonInfomation;
class GameEngineImageRenderer;
class MainPlayer : public GameEngineActor
{
private:	// 플레이어 정보
	CommonInfomation* PlayerInfomation_;

private: // 플레이어 부위별 애니메이션렌더러
	GameEngineRenderer* PlayerImageRenderer_;

public:
	MainPlayer();
	~MainPlayer();

protected:		// delete constructer
	MainPlayer(const MainPlayer& _other) = delete;
	MainPlayer(MainPlayer&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer& operator=(const MainPlayer& _other) = delete;
	MainPlayer& operator=(const MainPlayer&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


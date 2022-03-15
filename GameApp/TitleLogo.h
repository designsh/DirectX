#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 애니메이션
// 용도 : 타이틀레벨 로고
// 설명 : 
class GameEngineUIRenderer;
class TitleLogo : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* LogoAnimation_;

public:
	TitleLogo();
	~TitleLogo();

protected:		// delete constructer
	TitleLogo(const TitleLogo& _other) = delete;
	TitleLogo(TitleLogo&& _other) noexcept = delete;

private:		//delete operator
	TitleLogo& operator=(const TitleLogo& _other) = delete;
	TitleLogo& operator=(const TitleLogo&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


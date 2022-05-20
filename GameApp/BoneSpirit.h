#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineImageRenderer;
class GameEngineCollision;
class BoneSpirit : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Renderer_;
	GameEngineCollision* Collider_;

public:
	BoneSpirit();
	~BoneSpirit();

protected:		// delete constructer
	BoneSpirit(const BoneSpirit& _other) = delete;
	BoneSpirit(BoneSpirit&& _other) noexcept = delete;

private:		//delete operator
	BoneSpirit& operator=(const BoneSpirit& _other) = delete;
	BoneSpirit& operator=(const BoneSpirit&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


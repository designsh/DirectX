#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineImageRenderer;
class GameEngineCollision;
class AndarielProjectile : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Renderer_;
	GameEngineCollision* Collider_;

private:
	bool FireStart_;
	float4 MoveDir_;
	float MoveSpeed_;

private:
	int Damage_;

public:
	AndarielProjectile();
	~AndarielProjectile();

protected:		// delete constructer
	AndarielProjectile(const AndarielProjectile& _other) = delete;
	AndarielProjectile(AndarielProjectile&& _other) noexcept = delete;

private:		//delete operator
	AndarielProjectile& operator=(const AndarielProjectile& _other) = delete;
	AndarielProjectile& operator=(const AndarielProjectile&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private: // 타겟충돌처리
	void TargetCollision(GameEngineCollision* _Other);

private: // 해당 발사체관련 초기화
	void InitProjectile();
	void TextureCutting();
	void CreateAnimation();
	void CreateCollision();

public: // 생성과 동시에 해당 방향으로 발사
	void SkillAttackProjectile(float4 _MoveDir, int _Damage);
};


#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
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

private: // Ÿ���浹ó��
	void TargetCollision(GameEngineCollision* _Other);

private: // �ش� �߻�ü���� �ʱ�ȭ
	void InitProjectile();
	void TextureCutting();
	void CreateAnimation();
	void CreateCollision();

public: // ������ ���ÿ� �ش� �������� �߻�
	void SkillAttackProjectile(float4 _MoveDir, int _Damage);
};


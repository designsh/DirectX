#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ĳ����(��ũ�θǼ�)
// �뵵 : 
// ���� : 
class CommonInfomation;
class GameEngineImageRenderer;
class Necromancer : public GameEngineActor
{
private:	// member Var
	CommonInfomation* PlayerInfomation_;

private:
	GameEngineImageRenderer* PlayerImageRenderer;
	

public:
	Necromancer();
	~Necromancer();

protected:		// delete constructer
	Necromancer(const Necromancer& _other) = delete;
	Necromancer(Necromancer&& _other) noexcept = delete;

private:		//delete operator
	Necromancer& operator=(const Necromancer& _other) = delete;
	Necromancer& operator=(const Necromancer&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


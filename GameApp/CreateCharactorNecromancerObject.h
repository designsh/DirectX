#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 애니메이션
// 용도 : 캐릭터생성레벨 네크로맨서캐릭터
// 설명 : 
class CreateCharactorNecromancerObject : public GameEngineActor
{
private:	// member Var

public:
	CreateCharactorNecromancerObject();
	~CreateCharactorNecromancerObject();

protected:		// delete constructer
	CreateCharactorNecromancerObject(const CreateCharactorNecromancerObject& _other) = delete;
	CreateCharactorNecromancerObject(CreateCharactorNecromancerObject&& _other) noexcept = delete;

private:		//delete operator
	CreateCharactorNecromancerObject& operator=(const CreateCharactorNecromancerObject& _other) = delete;
	CreateCharactorNecromancerObject& operator=(const CreateCharactorNecromancerObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


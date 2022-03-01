#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 애니메이션
// 용도 : 캐릭터생성레벨 네크로맨서캐릭터
// 설명 : 
class CreateCharacterNecromancerObject : public GameEngineActor
{
private:	// member Var

public:
	CreateCharacterNecromancerObject();
	~CreateCharacterNecromancerObject();

protected:		// delete constructer
	CreateCharacterNecromancerObject(const CreateCharacterNecromancerObject& _other) = delete;
	CreateCharacterNecromancerObject(CreateCharacterNecromancerObject&& _other) noexcept = delete;

private:		//delete operator
	CreateCharacterNecromancerObject& operator=(const CreateCharacterNecromancerObject& _other) = delete;
	CreateCharacterNecromancerObject& operator=(const CreateCharacterNecromancerObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


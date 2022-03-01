#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 애니메이션
// 용도 : 캐릭터생성레벨 캠프파이어
// 설명 : 
class CreateCharactorFireObject : public GameEngineActor
{
private:	// member Var

public:
	CreateCharactorFireObject();
	~CreateCharactorFireObject();

protected:		// delete constructer
	CreateCharactorFireObject(const CreateCharactorFireObject& _other) = delete;
	CreateCharactorFireObject(CreateCharactorFireObject&& _other) noexcept = delete;

private:		//delete operator
	CreateCharactorFireObject& operator=(const CreateCharactorFireObject& _other) = delete;
	CreateCharactorFireObject& operator=(const CreateCharactorFireObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


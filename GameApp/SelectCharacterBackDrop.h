#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 이미지
// 용도 : 캐릭터선택레벨 배경
// 설명 : 
class GameEngineImageRenderer;
class SelectCharacterBackDrop : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* BackDrop_;

public:
	SelectCharacterBackDrop();
	~SelectCharacterBackDrop();

protected:		// delete constructer
	SelectCharacterBackDrop(const SelectCharacterBackDrop& _other) = delete;
	SelectCharacterBackDrop(SelectCharacterBackDrop&& _other) noexcept = delete;

private:		//delete operator
	SelectCharacterBackDrop& operator=(const SelectCharacterBackDrop& _other) = delete;
	SelectCharacterBackDrop& operator=(const SelectCharacterBackDrop&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


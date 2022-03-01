#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 이미지
// 용도 : 캐릭터선택레벨 셀렉터
// 설명 : 현재 게임시작하려는 플레이어를 선택
class GameEngineImageRenderer;
class SelectCharacterSelector : public GameEngineActor
{
private:	// member Var

public:
	SelectCharacterSelector();
	~SelectCharacterSelector();

protected:		// delete constructer
	SelectCharacterSelector(const SelectCharacterSelector& _other) = delete;
	SelectCharacterSelector(SelectCharacterSelector&& _other) noexcept = delete;

private:		//delete operator
	SelectCharacterSelector& operator=(const SelectCharacterSelector& _other) = delete;
	SelectCharacterSelector& operator=(const SelectCharacterSelector&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


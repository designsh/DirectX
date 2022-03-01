#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 캐릭터선택레벨 버튼
// 설명 : 해당 선택된 플레이어를 목록에서 삭제
class CharacterDeleteButton : public GameEngineActor
{
private:	// member Var

public:
	CharacterDeleteButton();
	~CharacterDeleteButton();

protected:		// delete constructer
	CharacterDeleteButton(const CharacterDeleteButton& _other) = delete;
	CharacterDeleteButton(CharacterDeleteButton&& _other) noexcept = delete;

private:		//delete operator
	CharacterDeleteButton& operator=(const CharacterDeleteButton& _other) = delete;
	CharacterDeleteButton& operator=(const CharacterDeleteButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


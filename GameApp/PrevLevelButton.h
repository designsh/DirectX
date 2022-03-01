#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 위젯
// 용도 : 캐릭터선택레벨 버튼
// 설명 : 타이틀레벨 이동
class PrevLevelButton : public GameEngineActor
{
private:	// member Var

public:
	PrevLevelButton();
	~PrevLevelButton();

protected:		// delete constructer
	PrevLevelButton(const PrevLevelButton& _other) = delete;
	PrevLevelButton(PrevLevelButton&& _other) noexcept = delete;

private:		//delete operator
	PrevLevelButton& operator=(const PrevLevelButton& _other) = delete;
	PrevLevelButton& operator=(const PrevLevelButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


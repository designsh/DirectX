#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : ĳ���ͼ��÷��� ��ư
// ���� : Ÿ��Ʋ���� �̵�
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


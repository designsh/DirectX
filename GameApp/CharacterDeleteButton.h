#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : ĳ���ͼ��÷��� ��ư
// ���� : �ش� ���õ� �÷��̾ ��Ͽ��� ����
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


#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : ĳ���ͼ��÷��� ��ư
// ���� : ĳ���ͻ������� �̵�
class CreateCharacterButton : public GameEngineActor
{
private:	// member Var

public:
	CreateCharacterButton();
	~CreateCharacterButton();

protected:		// delete constructer
	CreateCharacterButton(const CreateCharacterButton& _other) = delete;
	CreateCharacterButton(CreateCharacterButton&& _other) noexcept = delete;

private:		//delete operator
	CreateCharacterButton& operator=(const CreateCharacterButton& _other) = delete;
	CreateCharacterButton& operator=(const CreateCharacterButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : ĳ���ͻ������� ID�Է�â
// ���� : 
class CreateCharactorInputText : public GameEngineActor
{
private:	// member Var

public:
	CreateCharactorInputText();
	~CreateCharactorInputText();

protected:		// delete constructer
	CreateCharactorInputText(const CreateCharactorInputText& _other) = delete;
	CreateCharactorInputText(CreateCharactorInputText&& _other) noexcept = delete;

private:		//delete operator
	CreateCharactorInputText& operator=(const CreateCharactorInputText& _other) = delete;
	CreateCharactorInputText& operator=(const CreateCharactorInputText&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : ĳ���ͻ������� ID�Է�â
// ���� : ���콺�� �浹���̸�, ���콺 ���ʹ�ư Ŭ���� �ش� �ڽ��� Ȱ��ȭ�Ǹ�, Ű���� �Է����� ID�Է°���
//            �Էµ� ID�� �÷��̾��� �г����� �Ǹ�, �ش� �÷��̾� ������ ���ϸ��� �ȴ�.
class GameEngineUIRenderer;
class CreateCharacterInputText : public GameEngineActor
{
private:
	static std::string InputID;

public:
	static std::string GetInputID();

private:	// member Var
	GameEngineUIRenderer* IDInput_;

public:
	CreateCharacterInputText();
	~CreateCharacterInputText();

protected:		// delete constructer
	CreateCharacterInputText(const CreateCharacterInputText& _other) = delete;
	CreateCharacterInputText(CreateCharacterInputText&& _other) noexcept = delete;

private:		//delete operator
	CreateCharacterInputText& operator=(const CreateCharacterInputText& _other) = delete;
	CreateCharacterInputText& operator=(const CreateCharacterInputText&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


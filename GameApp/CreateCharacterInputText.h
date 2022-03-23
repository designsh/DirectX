#pragma once
#include <GameEngine/GameEngineActor.h>

#define ID_MAX_LEN 15

// �з� : ����
// �뵵 : ĳ���ͻ������� ID�Է�â
// ���� : ���콺�� �浹���̸�, ���콺 ���ʹ�ư Ŭ���� �ش� �ڽ��� Ȱ��ȭ�Ǹ�, Ű���� �Է����� ID�Է°���
//            �Էµ� ID�� �÷��̾��� �г����� �Ǹ�, �ش� �÷��̾� ������ ���ϸ��� �ȴ�.
class GameEngineUIRenderer;
class GameEngineCollision;
class CreateCharacterInputText : public GameEngineActor
{
private:
	static std::string InputText;

public:
	static std::string GetInputID();

private:	// member Var
	GameEngineUIRenderer*	IDInput_;			// ID �Է�â
	GameEngineCollision*	ActiveCollider_;	// ID �Է�â Ȱ��/��Ȱ�� ���� �Ǵ� �浹ü

private:
	bool InputBoxActive_;

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
	void ChangeStartReset();

public:
	void DebugRender();

public:
	void InputBoxActive(GameEngineCollision* _OtherCollision);
	void CharacterIDInput();
};


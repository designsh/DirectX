#pragma once
#include <GameEngine/GameEngineActor.h>

#define ID_MAX_LEN 10

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

private: // InputText Box ����
	GameEngineUIRenderer*	IDInput_;			// ID �Է�â

private: // InputText Caret ����
	GameEngineRenderer*		IDCaret_;			// ID �Է�â ĳ��(���θ޽�(��2��)�� �̿��ϴ� ���ĸ�������)

private: // Caret ����
	int CurCaretIndex_;

private: // ID ����(�Է°���)
	std::string InputText_;

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
	void DebugRender();
	void ChangeStartReset();

public:
	void CharacterIDInput();

public: // Input Text Function
	void AddText(const std::string& _Text);
	void DelText();

public: // Caret Function
	void SetCaretIndex();
	void AddCaretIndex(int _Index);
	void DelCaretIndex(int _Index);
};


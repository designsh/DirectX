#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �̹���
// �뵵 : ĳ���ͼ��÷��� ��ũ��
// ���� : ���� ������ �÷��̾��� ȭ��ǥ�� �ִ�ġ�� �Ѿ��� ��ũ���� �̿��Ͽ� 
//           ��� ����
class GameEngineImageRenderer;
class SelectCharacterScroll : public GameEngineActor
{
private:	// member Var

public:
	SelectCharacterScroll();
	~SelectCharacterScroll();

protected:		// delete constructer
	SelectCharacterScroll(const SelectCharacterScroll& _other) = delete;
	SelectCharacterScroll(SelectCharacterScroll&& _other) noexcept = delete;

private:		//delete operator
	SelectCharacterScroll& operator=(const SelectCharacterScroll& _other) = delete;
	SelectCharacterScroll& operator=(const SelectCharacterScroll&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


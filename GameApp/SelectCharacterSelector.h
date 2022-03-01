#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �̹���
// �뵵 : ĳ���ͼ��÷��� ������
// ���� : ���� ���ӽ����Ϸ��� �÷��̾ ����
class GameEngineImageRenderer;
class SelectCharacterSelector : public GameEngineActor
{
private:	// member Var

public:
	SelectCharacterSelector();
	~SelectCharacterSelector();

protected:		// delete constructer
	SelectCharacterSelector(const SelectCharacterSelector& _other) = delete;
	SelectCharacterSelector(SelectCharacterSelector&& _other) noexcept = delete;

private:		//delete operator
	SelectCharacterSelector& operator=(const SelectCharacterSelector& _other) = delete;
	SelectCharacterSelector& operator=(const SelectCharacterSelector&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


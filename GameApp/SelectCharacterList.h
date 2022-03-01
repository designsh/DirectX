#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ������
// �뵵 : �������
// ���� : ���� ������ ��� ĳ���� ���
class SelectCharacterList : public GameEngineActor
{
private:	// member Var

public:
	SelectCharacterList();
	~SelectCharacterList();

protected:		// delete constructer
	SelectCharacterList(const SelectCharacterList& _other) = delete;
	SelectCharacterList(SelectCharacterList&& _other) noexcept = delete;

private:		//delete operator
	SelectCharacterList& operator=(const SelectCharacterList& _other) = delete;
	SelectCharacterList& operator=(const SelectCharacterList&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


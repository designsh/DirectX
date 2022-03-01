#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 관리자
// 용도 : 관리목록
// 설명 : 현재 생성된 모든 캐릭터 목록
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


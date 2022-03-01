#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 이미지
// 용도 : 캐릭터선택레벨 스크롤
// 설명 : 현재 생성된 플레이어목록 화면표시 최대치가 넘어갈경우 스크롤을 이용하여 
//           목록 갱신
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


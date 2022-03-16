#pragma once
#include <GameEngine/GameEngineActor.h>

#define ID_MAX_LEN 10

// 분류 : 위젯
// 용도 : 캐릭터생성레벨 ID입력창
// 설명 : 마우스와 충돌중이며, 마우스 왼쪽버튼 클릭시 해당 박스가 활성화되며, 키보드 입력으로 ID입력가능
//            입력된 ID가 플레이어의 닉네임이 되며, 해당 플레이어 생성시 파일명이 된다.
class GameEngineUIRenderer;
class GameEngineCollision;
class CreateCharacterInputText : public GameEngineActor
{
private:
	static std::string InputText;

public:
	static std::string GetInputID();

private:	// member Var
	GameEngineUIRenderer*	IDInput_;			// ID 입력창
	GameEngineCollision*	ActiveCollider_;	// ID 입력창 활성/비활성 여부 판단 충돌체

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


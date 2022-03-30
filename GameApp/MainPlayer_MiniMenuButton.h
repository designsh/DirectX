#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �ٷΰ��� ����
enum class ShortcutsType
{
	NONE = -1,
	STATVIEW,
	INVENTORY,
	SKILLVIEW,
	GAMEENDMENU,
	MAX
};

// �з� : �ٷΰ��� ��ư
// �뵵 : 
// ���� : �޴���ư���̸�, �ش� �޴��� �ٷΰ���
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_MiniMenu;
class MainPlayer_MiniMenuButton : public GameEngineActor
{
private:
	MainPlayer_MiniMenu* Parent_;
	bool Active_;
	Button_State ButtonState_;
	ShortcutsType ShortcutsType_;

private:
	std::string DefaultButtonName_;
	std::string ClickButtonName_;
	float4 BasicButtonPos_;
	float4 MoveButtonPos_;

private:
	GameEngineUIRenderer* ButtonRenderer_;
	GameEngineCollision* ButtonCollision_;

public:
	MainPlayer_MiniMenuButton();
	~MainPlayer_MiniMenuButton();

protected:		// delete constructer
	MainPlayer_MiniMenuButton(const MainPlayer_MiniMenuButton& _other) = delete;
	MainPlayer_MiniMenuButton(MainPlayer_MiniMenuButton&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_MiniMenuButton& operator=(const MainPlayer_MiniMenuButton& _other) = delete;
	MainPlayer_MiniMenuButton& operator=(const MainPlayer_MiniMenuButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void ShortcutsButtonClick(GameEngineCollision* _Other);

public:
	void CreateShortcutsButton(MainPlayer_MiniMenu* _Parent, const std::string& _Name, const float4& _Pos, ShortcutsType _Type);

public:
	void ShortcutsProcess();
	void MoveButtonPosition();
};


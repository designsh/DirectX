#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 스킬 선택 타입
enum class DirectType
{
	None = -1,
	Left,
	Right
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_WeaponSkillButton : public GameEngineActor
{
private:	// member Var
	DirectType						DirectType_;				// 해당 스킬이 해당하는 타입(Left, Right)

private:
	int								SkillPage_;					// 해당 스킬 페이지 No
	int								SkillID_;					// 해당 스킬 ID
	int								PushNo_;					// 해당 스킬 목록에 추가된 순서
	std::string						ButtonName_;				// 스킬버튼 텍스쳐이름(기본,클릭,마을(비활성))
	float4							SkillBtnPos_;				// 스킬버튼 위치

private:
	Button_State					ButtonState_;				// 버튼 상태

private:
	GameEngineUIRenderer*			SkillButtonRenderer_;		// 스킬버튼 렌더러
	GameEngineCollision*			SkillButtonCollision_;		// 스킬버튼 충돌체

private:
	GameEngineCollision*			MoveableChkCol_;			// 플레이어 이동판단 체크용 충돌체

public:
	MainPlayer_WeaponSkillButton();
	~MainPlayer_WeaponSkillButton();

protected:		// delete constructer
	MainPlayer_WeaponSkillButton(const MainPlayer_WeaponSkillButton& _other) = delete;
	MainPlayer_WeaponSkillButton(MainPlayer_WeaponSkillButton&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_WeaponSkillButton& operator=(const MainPlayer_WeaponSkillButton& _other) = delete;
	MainPlayer_WeaponSkillButton& operator=(const MainPlayer_WeaponSkillButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SelectCurrentSkill(GameEngineCollision* _Other);

public:
	void CreateSkillButton(int _PushNo, const float4& _Pos, int _SkillID);
	void SetWeaponDirType(DirectType _DirType);
	void SelectCurWeapon(DirectType _DirType, int _SkillID, const std::string& _TextureName);
};


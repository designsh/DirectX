#pragma once

// 분류 : 글로벌 
// 용도 : 전역사용
// 설명 : 메인플레이어와 같이 여러 레벨에서 사용해야하는 정보를 가진 객체를 해당 클래스에서 관리
//            (주의!!!) 해당 값을 변경할때 주의해야한다.
class MainPlayer;
class MouseObject;
class MainPlayer_LeftWeaponSkillButton;
class MainPlayer_RightWeaponSkillButton;
class WeaponNPC;
class ChandleryNPC;
class TownMap;
class Portal;
class Storehouse;
class CatacombsMap;
class GlobalValue
{
public: // 플레이어 관련
	static MainPlayer* CurPlayer;
	static std::string CurPlayerID;

public: // 마우스관련
	static MouseObject* CurMouse;

public: // 스킬버튼관련(스킬목록생성시 지정됨)
	static MainPlayer_LeftWeaponSkillButton* CurLeftSkill;
	static MainPlayer_RightWeaponSkillButton* CurRightSkill;

public: // NPC 관련
	static WeaponNPC* WeaponNPC;
	static ChandleryNPC* ChandleryNPC;

public: // 맵관련
	static TownMap* TownMap;
	static CatacombsMap* CatacombsMap;

public: // 오브젝트관련
	// 공통
	static Portal* Portal;

	// 마을맵
	static Storehouse* Storehouse;

	// 카타콤맵
	

	// 카오스생츄어리맵
};


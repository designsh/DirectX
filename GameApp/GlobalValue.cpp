#include "PreCompile.h"
#include "GlobalValue.h"

// 사운드 관련
GameEngineSoundPlayer* GlobalValue::BackGroundSound = nullptr;

// 공통 UI관련
MonsterTopHPBar* GlobalValue::TopHPBar = nullptr;
SummonsEmblem* GlobalValue::Emblem = nullptr;

// 현재 생성된 게임의 메인플레이어
MainPlayer* GlobalValue::CurPlayer = nullptr;

// 현재 생성한 플레이어의 이름(ID)
// 캐릭터생성레벨에서 캐릭터를 만들면 기본정보를 생성하여 파일로 저장(ID.txt)
// 로딩레벨에서 생성한 캐릭터 정보를 로드하여 플레이어 정보생성
// 플레이레벨에서 게임종료시 현재 갱신된 플레이어 정보를 이용하여 기존파일 덮어씌우기
std::string GlobalValue::CurPlayerID = "";

// 현재 생성된 게임의 메인 마우스오브젝트
MouseObject* GlobalValue::CurMouse = nullptr;

// 현재 생성된 게임의 플레이어의 왼쪽스킬/오른쪽스킬
MainPlayer_LeftWeaponSkillButton* GlobalValue::CurLeftSkill = nullptr;
MainPlayer_RightWeaponSkillButton* GlobalValue::CurRightSkill = nullptr;

// 현재 생성된 게임의 NPC
WeaponNPC* GlobalValue::WeaponNPC = nullptr;
ChandleryNPC* GlobalValue::ChandleryNPC = nullptr;

// 맵관련
TownMap* GlobalValue::TownMap = nullptr;
CatacombsMap* GlobalValue::CatacombsMap = nullptr;

// 오브젝트관련
// 공통(레벨이 변경될때마다 변경된다.)
Portal* GlobalValue::Portal = nullptr;

// 마을맵(해당 맵에만 존재하는 오브젝트)
Storehouse* GlobalValue::Storehouse = nullptr;

// 카타콤맵(해당 맵에만 존재하는 오브젝트)


// 몬스터관련

// 보스
Andariel* GlobalValue::Andariel = nullptr;

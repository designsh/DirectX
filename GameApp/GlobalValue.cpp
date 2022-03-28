#include "PreCompile.h"
#include "GlobalValue.h"

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

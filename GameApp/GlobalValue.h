#pragma once

// 분류 : 글로벌 
// 용도 : 전역사용
// 설명 : 메인플레이어와 같이 여러 레벨에서 사용해야하는 정보를 가진 객체를 해당 클래스에서 관리
//            (주의!!!) 해당 값을 변경할때 주의해야한다.
class GameEngineUIRenderer;
struct WeaponSkillBtn_List
{
	int								SkillPage;					// 해당 스킬 페이지 No
	int								SkillID;					// 해당 스킬 ID
	int								PushNo;						// 해당 스킬 목록에 추가된 순서
	std::string						ButtonName;					// 스킬버튼 텍스쳐이름(기본,클릭,마을(비활성))
	GameEngineUIRenderer*			SkillButton;				// 스킬버튼 렌더러
	float4							SkillBtnPos;				// 스킬버튼 위치
};

class MainPlayer;
class MouseObject;
class GlobalValue
{
public: // 플레이어 관련
	static MainPlayer* CurPlayer;
	static std::string CurPlayerID;

public: // 마우스관련
	static MouseObject* CurMouse;

public:
};


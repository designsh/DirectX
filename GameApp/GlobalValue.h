#pragma once

// 분류 : 글로벌 
// 용도 : 전역사용
// 설명 : 메인플레이어와 같이 여러 레벨에서 사용해야하는 정보를 가진 객체를 해당 클래스에서 관리
//            (주의!!!) 해당 값을 변경할때 주의해야한다.
class MainPlayer;
class GlobalValue
{
public: // 플레이어 관련
	static MainPlayer* CurPlayer;
	static std::string CurPlayerID;
};


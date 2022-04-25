#pragma once

// 해당 맵의 벽정보와 오브젝트정보를 이용하여 생성
// 벽정보의 WALL,NONE 타입이면 이동불가지역으로 판단
// 오브젝트정보의 OBJECT,NONE 타입이면 이동불가지역으로 판단
enum class NavigationType
{
	NONE = -1,	// 수집실패
	NOR,		// 이동가능지역
	WALL,		// 이동불가지역
};

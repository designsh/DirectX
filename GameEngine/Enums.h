#pragma once

// 1. AABB 박스충돌 : 두 가지 모두 True여야만 충돌로 판정
//     1) 가로체크 : 두 사각형의 중점 가로 사이의 거리 < 두 사각형의 밑변 절반의 크기 합
//     2) 세로체크 : 두 사각형의 중점 세로 사이의 거리 < 두 사각형의 높이 절반의 크기 합
// 2. OBB 박스 충돌 : 내적을 이용한 투영으로 4가지를 체크하며 4가지 모두 True여야만 충돌로 판단
//      1) 오브젝트 1 Right축 기준 투영
//      2) 오브젝트 1 Up축 기준 투영
//      3) 오브젝트 2 Right축 기준 투영
//      4) 오브젝트 2 Up축 기준 투영
enum class CollisionType
{
	// 2D와 3D 충돌체간의 충돌은 금지한다.
	Point2D,					// 
	CirCle,						// 원
	Rect,							// 사각형
	OrientedRect,			// 회전한사각형

	Point3D,					// 
	Sphere3D,				// 구
	AABBBox3D,			// 박스
	OBBBox3D,				// 회전한박스
	MAX,
};

enum class RenderingOrder
{
	BackBuffer,
	World,
	UI,
	Debug,
};

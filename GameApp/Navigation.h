#pragma once

// 분류 : 
// 용도 : 
// 설명 : 각 레벨당 맵로드시 자동으로 맵정보를 이용하여 네비게이션 정보를 생성하기 위한 인터페이스 제공
class Navigation
{
private:	// member Var

protected:
	Navigation();
	virtual ~Navigation() = 0;

public:
	virtual bool FindPath(const float4& _Start, const float4& _Goal, std::vector<float4>& _vecPath) = 0;
};


#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class RandomMap
{
private:	// member Var

public:
	RandomMap();
	~RandomMap();

protected:		// delete constructer
	RandomMap(const RandomMap& _other) = delete;
	RandomMap(RandomMap&& _other) noexcept = delete;

private:		//delete operator
	RandomMap& operator=(const RandomMap& _other) = delete;
	RandomMap& operator=(const RandomMap&& _other) = delete;

public:
};


#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineRandom
{
private:	// member Var
	std::mt19937_64 mt_;

public:
	GameEngineRandom() :
		mt_()
	{
		std::random_device rng_;
		mt_.seed(rng_());
	}

	GameEngineRandom(__int64 _Seed) :
		mt_(_Seed)
	{
	}

	~GameEngineRandom()
	{
	}

protected:		// delete constructer
	GameEngineRandom(const GameEngineRandom& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRandom(GameEngineRandom&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRandom& operator=(const GameEngineRandom& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRandom& operator=(const GameEngineRandom&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	int RandomInt(int _min, int _max)
	{
		// 보통 대부분의 난수 알고리즘이
		// 마지막 제한을 할때 % 사용하므로
		// 보통 _max -1까지 나온다는것을 항상 염두해 둬야 합니다.
		std::uniform_int_distribution<int> Dis(_min, _max);
		return Dis(mt_);
	}

	float RandomFloat(float _min, float _max)
	{
		// 보통 대부분의 난수 알고리즘이
		// 마지막 제한을 할때 % 사용하므로
		// 보통 _max -1까지 나온다는것을 항상 염두해 둬야 합니다.
		std::uniform_real_distribution<float> Dis(_min, _max);
		return Dis(mt_);
	}
};


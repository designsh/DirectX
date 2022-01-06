#pragma once

// �з� : 
// �뵵 : 
// ���� : 
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
	GameEngineRandom(const GameEngineRandom& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRandom(GameEngineRandom&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRandom& operator=(const GameEngineRandom& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRandom& operator=(const GameEngineRandom&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	int RandomInt(int _min, int _max)
	{
		// ���� ��κ��� ���� �˰�����
		// ������ ������ �Ҷ� % ����ϹǷ�
		// ���� _max -1���� ���´ٴ°��� �׻� ������ �־� �մϴ�.
		std::uniform_int_distribution<int> Dis(_min, _max);
		return Dis(mt_);
	}

	float RandomFloat(float _min, float _max)
	{
		// ���� ��κ��� ���� �˰�����
		// ������ ������ �Ҷ� % ����ϹǷ�
		// ���� _max -1���� ���´ٴ°��� �׻� ������ �־� �մϴ�.
		std::uniform_real_distribution<float> Dis(_min, _max);
		return Dis(mt_);
	}
};


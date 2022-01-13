#pragma once
#include <math.h>
#include <random>
#include <string>
#include <Windows.h>

class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;
	static const float DegreeToRadian;
	static const float RadianToDegree;
};

class float4
{
public:
	static const float4 ZERO;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;

public:
	static float4 RotateYDegree(float4 _OriginVector, float _Degree)
	{
		return RotateYRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateYRadian(float4 _OriginVector, float _Radian)
	{
		float4 NextVector;

		NextVector.z = _OriginVector.z * cosf(_Radian) - _OriginVector.x * sinf(_Radian);
		NextVector.x = _OriginVector.z * sinf(_Radian) + _OriginVector.x * cosf(_Radian);
		NextVector.y = _OriginVector.y;

		return NextVector;
	}

	static float4 RotateXDegree(float4 _OriginVector, float _Degree)
	{
		return RotateXRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateXRadian(float4 _OriginVector, float _Radian)
	{
		float4 NextVector;

		NextVector.y = _OriginVector.y * cosf(_Radian) - _OriginVector.z * sinf(_Radian);
		NextVector.z = _OriginVector.y * sinf(_Radian) + _OriginVector.z * cosf(_Radian);
		NextVector.x = _OriginVector.x;
		
		return NextVector;
	}


	static float4 RotateZDegree(float4 _OriginVector, float _Degree)
	{
		return RotateZRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateZRadian(float4 _OriginVector, float _Radian)
	{
		float4 NextVector;

		NextVector.x = _OriginVector.x * cosf(_Radian) - _OriginVector.y * sinf(_Radian);
		NextVector.y = _OriginVector.x * sinf(_Radian) + _OriginVector.y * cosf(_Radian);
		NextVector.z = _OriginVector.z;

		return NextVector;
	}

	static float4 DirZDegree(float _Degree)
	{
		return DirZRadian(_Degree * GameEngineMath::DegreeToRadian);
	}

	// 0도 {1, 0} 일때의 벡터를 회전시키는 공식인겁니다.
	static float4 DirZRadian(float _Radian)
	{
		return float4(cosf(_Radian), sinf(_Radian));
	}

public:
	// unnamed union을 선언하면 
	// 내부의 메모리를 구조를 union 방식으로 구성해준다.
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		// 실수는 기본적으로 00000000 00000000 00000000 00000000
	};

	float4 operator+(const float4 _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x + _other.x;
		ReturnValue.y = this->y + _other.y;
		ReturnValue.z = this->z + _other.z;
		ReturnValue.w = this->w + _other.w;
		return ReturnValue;
	}

	float4 operator-(const float4 _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x - _other.x;
		ReturnValue.y = this->y - _other.y;
		ReturnValue.z = this->z - _other.z;
		ReturnValue.w = this->w - _other.w;
		return ReturnValue;
	}

	float4 operator*(const float _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x * _other;
		ReturnValue.y = this->y * _other;
		ReturnValue.z = this->z * _other;
		ReturnValue.w = this->w * _other;
		return ReturnValue;
	}



	float4 operator*(const float4 _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x * _other.x;
		ReturnValue.y = this->y * _other.y;
		ReturnValue.z = this->z * _other.z;
		ReturnValue.w = this->w * _other.w;
		return ReturnValue;
	}

	float4 operator/(const float4 _other) const
	{
		float4 ReturnValue;

		ReturnValue.x = this->x / _other.x;
		ReturnValue.y = this->y / _other.y;
		ReturnValue.z = this->z / _other.z;
		ReturnValue.w = this->w / _other.w;
		return ReturnValue;
	}


	float4& operator+=(const float4 _other)
	{
		this->x += _other.x;
		this->y += _other.y;
		this->z += _other.z;
		this->w += _other.w;
		return *this;
	}

	float4& operator-=(const float4 _other)
	{
		this->x -= _other.x;
		this->y -= _other.y;
		this->z -= _other.z;
		this->w -= _other.w;
		return *this;
	}

	float4& operator*=(const float4 _other)
	{
		this->x *= _other.x;
		this->y *= _other.y;
		this->z *= _other.z;
		this->w *= _other.w;
		return *this;
	}

	float4& operator*=(const float _Value)
	{
		this->x *= _Value;
		this->y *= _Value;
		this->z *= _Value;
		this->w *= _Value;
		return *this;
	}

	float4& operator/=(const float4 _other)
	{
		this->x /= _other.x;
		this->y /= _other.y;
		this->z /= _other.z;
		this->w /= _other.w;
		return *this;
	}

	// 대입연산자
	float4& operator=(const float4& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
		w = _other.w;

		return *this;
	}

public:
	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}


	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float4 halffloat4() const
	{
		return { hx(), hy(), hz() };
	}

	int ihx() const
	{
		return static_cast<int>(hx());
	}

	int ihy() const
	{
		return static_cast<int>(hy());
	}

	int ihz() const
	{
		return static_cast<int>(hz());
	}

	POINT GetWindowPoint()
	{
		return { ix(), iy() };
	}

	void RotateXDegree(float _Deg)
	{
		*this = RotateXDegree(*this, _Deg);
		return;
	}

	void RotateYDegree(float _Deg)
	{
		*this = RotateYDegree(*this, _Deg);
		return;
	}

	void RotateZDegree(float _Deg)
	{
		*this = RotateZDegree(*this, _Deg);
		return;
	}


public:
	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{
	}

	// 디폴트 파라미터
	// 가장 우측에 있는 인자에 상수값을 넣어서
	// 만약 인자를 넣어주지 않았을때는 
	float4(float _x, float _y, float _z, float _w = 1.0f)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	~float4() {

	}

public:		// delete constructer
	float4(const float4& _other)
		: x(_other.x), y(_other.y), z(_other.z), w(_other.w)
	{

	}

};

class int4
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct
		{
			__int64 HighValue;
			__int64 LowValue;
		};
	};
};


class Figure
{
public:
	float4 pos_;
	float4 size_;

public:
	float Left()
	{
		return pos_.x - size_.hx();
	}

	float Right()
	{
		return pos_.x + size_.hx();
	}

	float Top()
	{
		return pos_.y - size_.hy();
	}

	float Bot()
	{
		return pos_.y + size_.hx();
	}

	int iLeft()
	{
		return pos_.ix() - size_.ihx();
	}

	int iRight()
	{
		return pos_.ix() + size_.ihx();
	}

	int iTop()
	{
		return pos_.iy() - size_.ihy();
	}

	int iBot()
	{
		return pos_.iy() + size_.ihy();
	}

	float4 LeftTopfloat4()
	{
		return { Left(), Top() };
	}

	float4 RightTopfloat4()
	{
		return { Right(), Top() };
	}

	float4 LeftBotfloat4()
	{
		return { Left(), Bot() };
	}

	float4 RightBotfloat4()
	{
		return { Right(), Bot() };
	}


public:
	Figure(float4 _Pos, float4 _Size)
		: pos_(_Pos), size_(_Size)
	{

	}
};

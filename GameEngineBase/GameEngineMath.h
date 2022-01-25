#pragma once

class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;
	static const float DegreeToRadian;
	static const float RadianToDegree;
};

class float4x4;
class float4
{
public:
	static const float4 ZERO;
	static const float4 ONE;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;

	static const float4 RED;
	static const float4 BLUE;
	static const float4 GREEN;
	static const float4 WHITE;
	static const float4 BLACK;
	static const float4 NONE;

public:
	// 외적 : 두 벡터를 외적(두 벡터를 외적하면 두 벡터에 모두 수직인 벡터 도출)
	static float4 Cross3D(float4 _Left, float4 _Right)
	{
		return DirectX::XMVector3Cross(_Left.DirectVector, _Right.DirectVector);
	}

	// 내적 : 두 벡터를 내적(COS(세타)를 도출)
	static float Dot3D(float4 _Left, float4 _Right)
	{
		return DirectX::XMVector3Dot(_Left.DirectVector, _Right.DirectVector).m128_f32[0];
	}

	// 정사영 : 두벡터를 내적하여 정사영 길이를 도출(단, 둘중 하나의 벡터가 반드시 단위벡터이어야만 정사영길이 도출)
	static float Dot3DToLen(float4 _Left, float4 _Right)
	{
		_Right.Normalize3D();
		return DirectX::XMVector3Dot(_Left.DirectVector, _Right.DirectVector).m128_f32[0];
	}

	// 내적하는 두 벡터를 단위벡터화(크기가 1인  벡터)하여 두 벡터를 내적하여 COS(세타) 값을 도출
	static float Dot3DToCos(float4 _Left, float4 _Right)
	{
		_Left.Normalize3D();
		_Right.Normalize3D();
		return DirectX::XMVector3Dot(_Left.DirectVector, _Right.DirectVector).m128_f32[0];
	}

	// 역함수 : cos세타에서 cos을 제외하고 라디안(각도)값을 도출
	static float Dot3DToCosAngle(float4 _Left, float4 _Right)
	{
		return acos(Dot3DToCos(_Left, _Right));
	}

	static float4 RotateYDegree(float4 _OriginVector, float _Degree)
	{
		return RotateYRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}
	static float4 RotateYRadian(float4 _OriginVector, float _Radian);

	static float4 RotateXDegree(float4 _OriginVector, float _Degree)
	{
		return RotateXRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}
	static float4 RotateXRadian(float4 _OriginVector, float _Radian);

	static float4 RotateZDegree(float4 _OriginVector, float _Degree)
	{
		return RotateZRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}
	static float4 RotateZRadian(float4 _OriginVector, float _Radian);

	static float4 DirZDegree(float _Degree)
	{
		return DirZRadian(_Degree * GameEngineMath::DegreeToRadian);
	}

	// 0도 {1, 0} 일때의 벡터를 회전시키는 공식인겁니다.
	static float4 DirZRadian(float _Radian);

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

		DirectX::XMFLOAT3 DxXmfloat3;
		DirectX::XMFLOAT4 DxXmfloat4;

		DirectX::XMVECTOR DirectVector;
	};

	float4 operator+(const float4 _value) const
	{
		return DirectX::XMVectorAdd(DirectVector, _value.DirectVector);
	}

	float4 operator-() const
	{
		return DirectX::XMVectorNegate(DirectVector);
	}

	float4 operator-(const float4 _value) const
	{
		return DirectX::XMVectorSubtract(DirectVector, _value.DirectVector);
	}

	float4 operator*(const float _value) const
	{
		float4 CalVector = { _value , _value , _value , 1.0f };
		return DirectX::XMVectorMultiply(DirectVector, CalVector.DirectVector);
	}

	float4 operator*(const float4x4& _Value) const;
	float4& operator*=(const float4x4& _Value);

	float4 operator*(const float4 _value) const
	{
		return DirectX::XMVectorMultiply(DirectVector, _value.DirectVector);
	}

	float4 operator/(const float4 _value) const
	{
		return DirectX::XMVectorDivide(DirectVector, _value.DirectVector);
	}


	float4& operator+=(const float4 _value)
	{
		DirectVector = DirectX::XMVectorAdd(DirectVector, _value.DirectVector);
		return *this;
	}

	float4& operator-=(const float4 _value)
	{
		DirectVector = DirectX::XMVectorSubtract(DirectVector, _value.DirectVector);
		return *this;
	}

	float4& operator*=(const float4 _value)
	{
		DirectVector = DirectX::XMVectorMultiply(DirectVector, _value.DirectVector);
		return *this;
	}

	float4& operator*=(const float _Value)
	{
		float4 Value = float4(_Value, _Value, _Value, 1.0f);
		DirectVector = DirectX::XMVectorMultiply(DirectVector, Value.DirectVector);
		return *this;
	}


	float4& operator/=(const float4& _Value)
	{
		DirectVector = DirectX::XMVectorDivide(DirectVector, _Value.DirectVector);
		return *this;
	}

	// 대입연산자
	float4& operator=(const float4& _value)
	{
		DirectVector = DirectX::XMVectorSet(_value.x, _value.y, _value.z, _value.w);
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

	int uix() const
	{
		return static_cast<unsigned int>(x);
	}

	int uiy() const
	{
		return static_cast<unsigned int>(y);
	}

	int uiz() const
	{
		return static_cast<unsigned int>(z);
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

	float Len3D()
	{
		float4 Len = DirectX::XMVector3Length(DirectVector);
		return Len.x;
	}

	float4 NormalizeReturn3D() const
	{
		return DirectX::XMVector3Normalize(DirectVector);
	}

	void Normalize3D()
	{
		DirectVector = DirectX::XMVector3Normalize(DirectVector);
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

	float4(DirectX::XMVECTOR _value)
		: DirectVector(_value)
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

// 행렬
class float4x4
{
public:
	union
	{
		float Arr2D[4][4];

		struct
		{
			float4 vx;
			float4 vy;
			float4 vz;
			float4 vw;
		};

		float Arr1D[4 * 4];

		DirectX::XMFLOAT4X4 DxXmfloat4x4;
		DirectX::XMMATRIX DirectMatrix;
	};

public:
	float4x4() : 
		DirectMatrix(DirectX::XMMatrixIdentity())
	{

	}

	float4x4(const float4x4& _Other) :
		DirectMatrix(_Other.DirectMatrix)
	{

	}

	float4x4(const DirectX::XMMATRIX& _Other) :
		DirectMatrix(_Other)
	{

	}

	~float4x4()
	{

	}

public:
	float4x4 operator*(const float4x4& _value)
	{
		return DirectX::XMMatrixMultiply(DirectMatrix, _value.DirectMatrix);
	}

public:
	// 크기변환 행렬
	void Scaling(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixScalingFromVector(_Value.DirectVector);
	}

	// 위치변환 행렬
	void Translation(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value.DirectVector);
	}

	// 회전변환 행렬
	void RotationDeg(const float4& _Value)
	{
		RotationRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationXDeg(const float& _Value)
	{
		RotationXRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationYDeg(const float& _Value)
	{
		RotationYRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationZDeg(const float& _Value)
	{
		RotationZRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationRad(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(_Value.DirectVector);
	}

	void RotationXRad(const float& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationX(_Value);
	}

	void RotationYRad(const float& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationY(_Value);
	}

	void RotationZRad(const float& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationZ(_Value);
	}
	
public: // 단위행렬 생성
	void Identity()
	{
		DirectMatrix = DirectX::XMMatrixIdentity();
	}

public: // 전치행렬 : 주대각선(LT->RB)를 기준으로 반사대칭한 행렬 생성
	void Transpose()
	{
		DirectMatrix = DirectX::XMMatrixTranspose(DirectMatrix);
	}

public: // 뷰포트
	void ViewPortCenter(float _ScreenX, float _ScreenY, float _StartX, float _StartY, float _MinZ, float _MaxZ)
	{
		Identity();

		Arr2D[0][0] = _ScreenX * 0.5f;
		Arr2D[1][1] = -_ScreenY * 0.5f;
		Arr2D[2][2] = _MaxZ - _MinZ;
		Arr2D[3][0] = _StartX + Arr2D[0][0];
		Arr2D[3][1] = _ScreenY * 0.5f + _StartY;
		Arr2D[3][2] = _MinZ;
	}

public: // 뷰행렬
	// 관측자가 어떠한 물체를 바라본다.
	void ViewAtLH(const float4& _EyePos, const float4& _EyeFocus, const float4& _EyeUp)
	{
		DirectMatrix = DirectX::XMMatrixLookAtLH(_EyePos.DirectVector, _EyeFocus.DirectVector, _EyeUp.DirectVector);
	}

	// 관측자가 어떠한 방향을 바라본다.
	void ViewToLH(const float4& _EyePos, const float4& _EyeFocus, const float4& _EyeUp)
	{
		DirectMatrix = DirectX::XMMatrixLookToLH(_EyePos.DirectVector, _EyeFocus.DirectVector, _EyeUp.DirectVector);
	}

public: // 투영행렬
	// 원근투영
	void PerspectiveFovLH(float _FovAngleY, float _Width, float _Height, float _NearZ, float _FarZ)
	{
		// 거의 대부분의 수학공식은 라디안을 기준으로 하기때문에 360분법으로 인자를 받아와 라디안으로 변환해야한다.
		PerspectiveFovLH(_FovAngleY * GameEngineMath::DegreeToRadian, _Width / _Height, _NearZ, _FarZ);
	}

	void PerspectiveFovLH(float _FovAngleY, float _AspectRatio, float _Near, float _Far)
	{
		// 월드행렬*뷰행렬 까지의 어떠한 벡터(정점)의 Z값을 이용하여 화면상에서의 비율(모니터)을 계산하기 때문에
		// 원근투영행렬이 곱해질때 z값을 보존하기위하여 (2,4) 원소(w)에 z값을 저장해놓는다.
		// 그러므로 월드행렬*뷰행렬*원근투영행렬에 의해 변환이 일어난 정점(벡터)는 
		// 0.1 0   0   0
		// 0   0.1 0   0
		// 0   0   0.1 1 <- 본래의 z값 보존
		// 0   0   0   0 
		// 위와 같은 행렬이 생성된다.
		// 이후 실질적인 비율계산은 Rasterizer단계에서 처리한다.
		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngleY, _AspectRatio, _Near, _Far);
	}

	// 직교투영
	void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	{
		DirectMatrix = DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);
	}
};

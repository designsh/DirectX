#pragma once
#include "GameEngineComponent.h"

#include <DirectXCollision.h>
#include <DirectXCollision.inl>

union CollisionData
{
public:
	DirectX::BoundingSphere				Sphere;		// 구
	DirectX::BoundingBox				AABB;		// 회전이 고려하면 안되는 박스
	DirectX::BoundingOrientedBox		OBB;		// 회전한 박스

	CollisionData() : OBB()
	{
	}
};

// 각 물체의 지역 공간상의 위치, 크기, 회전 정보와 월드 공간상의 위치, 크기, 회전 정보를 통하여
// 생성하는 각각의 행렬을 관리하는 클래스
class TransformData
{
public:
	// 월드 : 월드 공간에서의 원점(0,0,0)을 기준
	float4 vWorldPosition_;
	float4 vWorldRotation_;
	float4 vWorldScaling_;

	// 로컬 : 1. 부모 O : 부모의 위치(원점)을 기준
	//            2. 부모 X : 월드 공간에서의 원점(0,0,0)을 기준
	// Ex) A컴포넌트의 자식 컴포넌트가 B컴포넌트라고 가정한다면
	//        B컴포넌트의 로컬위치는 A컴포넌트의 위치(100, 0, 0)이라면
	//        A컴포넌트의 위치(100,0,0)로부터의 B컴포넌트의 위치가 설정된다
	//        A컴포넌트와 B컴포넌트가 겹쳐서 생성되었다면 A컴포넌트의 로컬위치는 최상위 컴포넌트이므로
	//        100,0,0이 로컬위치가 되고, B컴포넌트는 100,0,0이 원점이므로 위치는 0,0,0이 된다.
	float4 vLocalPosition_;
	float4 vLocalRotation_;
	float4 vLocalScaling_;

	// 변환행렬
	float4x4 LocalScaling_;
	float4x4 LocalRotation_;
	float4x4 LocalPosition_;
	float4x4 LocalWorld_;

	// 부모행렬
	float4x4 Parent_;

	// 월드행렬
	float4x4 WorldWorld_;

	// 뷰행렬
	float4x4 View_;

	// 투영행렬
	float4x4 Projection_;

	// 최종행렬
	float4x4 WVP;

public:
	TransformData() : 
		vWorldScaling_(float4::ONE), 
		vLocalScaling_(float4::ONE)
	{
	}

public:
	// 로컬행렬(크기/회전/위치/월드) 생성
	void LocalCalculation()
	{
		LocalScaling_.Scaling(vLocalScaling_);
		LocalRotation_.RotationDeg(vLocalRotation_);
		LocalPosition_.Translation(vLocalPosition_);

		LocalWorld_ = LocalScaling_ * LocalRotation_ * LocalPosition_;
	}

	// 부모셋팅 : 부모가 존재한다면 모든 행렬이 계산될때 부모의 행렬의 영향을 받는다.
	void ParentSetting(const float4x4& _Parent)
	{
		Parent_ = _Parent;
		WorldWorld_ = LocalWorld_;
		WorldWorld_ *= Parent_;
	}

	// 자신의 부모가 존재하지 않는다.
	// 자신이 최상위 트랜스폼이므로 부모의 영향을 받지않는다.
	void RootCalculation()
	{
		WorldWorld_ = LocalWorld_;
	}

	// 최종행렬을 계산
	void WVPCalculation()
	{
		WVP = WorldWorld_ * View_ * Projection_;
	}
};

// 분류 : 트랜스폼(Transform)
// 용도 : 
// 설명 : 각 물체의 지역좌표상의 위치, 크기, 회전 정보를 정의하는 기능을 제공하고 이를 월드상의 좌표(World Space)로 변환하는 기능을 제공하는 클래스
//            단, 각 물체는 부모 물체를 가지고 있는 계층구조(부모-자식)를 이루며 사용자의 선택에 따라 부모의 영향을 받아 위치/크기/회전 정보를 계산하는 경우도 있다.
class GameEngineTransform
{
private:	// member Var
	TransformData									TransformData_;		// 로컬/월드 크기/회전/위치 및 공전, 부모 행렬을 제공하는 트랜스폼 정보
	GameEngineTransform*							Parent_;			// 현재 트랜스폼의 부모 트랜스폼
	std::vector<GameEngineTransform*>				Childs_;			// 현재 트랜스폼의 자식 트랜스폼 목록

private:
	CollisionData									ColData_;			// 

public:
	GameEngineTransform();
	~GameEngineTransform();

private:		//delete operator
	GameEngineTransform& operator=(const GameEngineTransform& _other) = delete;
	GameEngineTransform& operator=(const GameEngineTransform&& _other) = delete;

public:
	void AttachTransform(GameEngineTransform* _Transform);
	void DetachChildTransform(GameEngineTransform* _Transform);

public:
	TransformData& GetTransformData();

public: // 충돌체 관련
	inline const CollisionData& GetCollisionData()
	{
		return ColData_;
	}

	inline const DirectX::BoundingSphere& GetSphere()
	{
		return ColData_.Sphere;
	}

	inline const DirectX::BoundingOrientedBox& GetOBB()
	{
		return ColData_.OBB;
	}

	inline const DirectX::BoundingBox& GetAABB()
	{
		return ColData_.AABB;
	}

private: // 내부처리
	void AllChildCalculationScaling();						// 모든 자식의 크기변화를 계산(부모가 존재한다면 부모행렬의 영향을 받음)
	void AllChildCalculationRotation();						// 모든 자식의 회전변화를 계산(부모가 존재한다면 부모행렬의 영향을 받음)
	void AllChildCalculationPosition();						// 모든 자식의 위치변화를 계산(부모가 존재한다면 부모행렬의 영향을 받음)

	// 크기행렬
	void CalculationLocalScaling();							// 자신의 로컬 크기행렬을 계산
	void CalculationWorldScaling();							// 자신의 월드 크기행렬을 계산

	// 회전행렬
	void CalculationLocalRotation();						// 자신의 로컬 회전행렬을 계산
	void CalculationWorldRotation();						// 자신의 월드 회전행렬을 계산

	// 이동행렬
	void CalculationLocalPosition();						// 자신의 로컬 위치행렬을 계산
	void CalculationWorldPosition();						// 자신의 월드 위치행렬을 계산

public:
	void SetLocalScaling(const float4& _Value);				// 자신의 로컬크기를 Set
	void SetWorldScaling(const float4& _Value);				// 자신의 월드크기를 Set
	void SetLocalRotationDegree(const float4& _Value);		// 자신의 로컬회전을 Set
	void SetWorldRotationDegree(const float4& _Value);		// 자신의 월드회전을 Set
	void SetLocalPosition(const float4& _Value);			// 자신의 로컬위치를 Set
	void SetWorldPosition(const float4& _Value);			// 자신의 월드위치를 Set

public:
	void AddLocalDeltaTimeRotation(const float4& _Value);	// DeltaTime 영향을 받아 로컬회전
	void AddWorldDeltaTimeRotation(const float4& _Value);	// DeltaTime 영향을 받아 월드회전
	void SetLocalDeltaTimeMove(const float4& _Value);		// DeltaTime 영향을 받아 로컬이동
	void SetWorldDeltaTimeMove(const float4& _Value);		// DeltaTime 영향을 받아 월드이동

public:
	void AddLocalRotationDegreeX(const float _Value);		// 
	void AddWorldRotationDegreeX(const float _Value);		// 
	void AddLocalRotationDegreeY(const float _Value);		// 
	void AddWorldRotationDegreeY(const float _Value);		// 
	void AddLocalRotationDegreeZ(const float _Value);		// 
	void AddWorldRotationDegreeZ(const float _Value);		// 

public: // Normal Update 관련
	void SetLocalMove(const float4& _Value);				// _Value만큼 로컬이동
	void SetWorldMove(const float4& _Value);				// _Value만큼 월드이동

public:
	void SetLocalZOrder(float _Value);						// ZOrder 셋팅(로컬)
	void SetWorldZOrder(float _Value);						// ZOrder 셋팅(월드)

public:
	void Copy(const GameEngineTransform& _Other);			// 프리카메라 사용전 트랜스폼데이터로 되돌리기

public: // 기본 상수버퍼 관련
	float4 GetLocalScaling() const;
	float4 GetWorldScaling() const;
	float4 GetLocalRotation() const;
	float4 GetWorldRotation() const;
	float4 GetLocalPosition() const;
	float4 GetWorldPosition() const;

public: // 카메라 관련
	float4 GetWorldForwardVector() const;
	float4 GetLocalForwardVector() const;
	float4 GetWorldRightVector() const;
	float4 GetLocalRightVector() const;
	float4 GetWorldUpVector() const;
	float4 GetLocalUpVector() const;
	float4 GetWorldBackVector() const;
	float4 GetLocalBackVector() const;
	float4 GetWorldLeftVector() const;
	float4 GetLocalLeftVector() const;
	float4 GetWorldDownVector() const;
	float4 GetLocalDownVector() const;

public:
	void TransformUpdate();									// 정보 갱신 및 셰이더에 전달하는 물체의 정보 갱신
};


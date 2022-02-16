#pragma once
#include "GameEngineComponent.h"

class TransformData
{
public:
	// 월드
	float4 vWorldPosition_;
	float4 vWorldRotation_;
	float4 vWorldScaling_;

	// 로컬
	float4 vLocalPosition_;
	float4 vLocalRotation_;
	float4 vLocalScaling_;

	// 변환행렬
	float4x4 LocalScaling_;
	float4x4 LocalRotation_;
	float4x4 LocalPosition_;
	float4x4 LocalWorld_;

	float4x4 Parent_;
	float4x4 WorldWorld_;

	float4x4 View_;
	float4x4 Projection_;

public:
	// 로컬 행렬 생성
	void LocalCalculation()
	{
		LocalScaling_.Scaling(vLocalScaling_);
		LocalRotation_.RotationDeg(vLocalRotation_);
		LocalPosition_.Translation(vLocalPosition_);

		LocalWorld_ = LocalScaling_ * LocalRotation_ * LocalPosition_;
	}

	// 자신의 부모가 존재한다
	void ParentSetting(const float4x4& _Parent)
	{
		Parent_ = _Parent;
		WorldWorld_ = LocalWorld_;
		WorldWorld_ *= Parent_;
	}

	// 자신의 부모가 존재하지 않는다.
	void RootCalculation()
	{
		WorldWorld_ = LocalWorld_;
	}
};

// 분류 : 트랜스폼(Transform)
// 용도 : 
// 설명 : 각 물체의 지역좌표상의 위치, 크기, 회전 정보를 정의하는 기능을 제공하고 이를 월드상의 좌표(World Space)로 변환하는 기능을 제공하는 클래스
//            단, 각 물체는 부모 물체를 가지고 있는 계층구조(부모-자식)를 이루며 사용자의 선택에 따라 부모의 영향을 받아 위치/크기/회전 정보를 계산하는 경우도 있다.
class GameEngineTransform
{
private:	// member Var
	TransformData										TransData_;		// 로컬/월드 크기/회전/위치 및 공전, 부모 행렬을 제공하는 트랜스폼 정보
	GameEngineTransform*						Parent_;				// 현재 트랜스폼의 부모 트랜스폼
	std::list<GameEngineTransform*>	Childs_;				// 현재 트랜스폼의 자식 트랜스폼 목록

public:
	GameEngineTransform();
	~GameEngineTransform();

protected:		// delete constructer
	GameEngineTransform(const GameEngineTransform& _other) = delete;
	GameEngineTransform(GameEngineTransform&& _other) noexcept = delete;

private:		//delete operator
	GameEngineTransform& operator=(const GameEngineTransform& _other) = delete;
	GameEngineTransform& operator=(const GameEngineTransform&& _other) = delete;

public:
	void SetParent(GameEngineTransform* _Parent);
	void DetachChild(GameEngineTransform* _Child);

private: // 내부처리
	void AllChildCalculationScaling();									// 모든 자식의 크기변화를 계산(부모가 존재한다면 부모행렬의 영향을 받음)
	void AllChildCalculationRotation();								// 모든 자식의 회전변화를 계산(부모가 존재한다면 부모행렬의 영향을 받음)
	void AllChildCalculationPosition();								// 모든 자식의 위치변화를 계산(부모가 존재한다면 부모행렬의 영향을 받음)

	// 크기행렬
	void CalculationLocalScaling();										// 자신의 로컬 크기행렬을 계산
	void CalculationWorldScaling();										// 자신의 월드 크기행렬을 계산

	// 회전행렬
	void CalculationLocalRotation();									// 자신의 로컬 회전행렬을 계산
	void CalculationWorldRotation();									// 자신의 월드 회전행렬을 계산

	// 이동행렬
	void CalculationLocalPosition();										// 자신의 로컬 위치행렬을 계산
	void CalculationWorldPosition();									// 자신의 월드 위치행렬을 계산

public:
	void SetLocalScaling(const float4& _Value);				// 자신의 로컬크기를 Set
	void SetWorldScaling(const float4& _Value);				// 자신의 월드크기를 Set

	void SetLocalRotation(const float4& _Value);			// 자신의 로컬회전을 Set
	void SetWorldRotation(const float4& _Value);			// 자신의 월드회전을 Set

	void SetLocalPosition(const float4& _Value);				// 자신의 로컬위치를 Set
	void SetWorldPosition(const float4& _Value);			// 자신의 월드위치를 Set

public:
	void TransformUpdate();													// 정보 갱신 및 셰이더에 전달하는 물체의 정보 갱신
};


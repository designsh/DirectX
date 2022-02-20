#pragma once
#include "GameEngineTransformComponent.h"

// 투영 타입
enum class ProjectionMode
{
	Perspective,
	Orthographic
};

// 분류 : 카메라 컴포넌트
// 용도 : 
// 설명 : 
class CameraComponent : public GameEngineTransformComponent
{
	friend class CameraActor;

private:	// member Var
	ProjectionMode	ProjectionMode_;			// 
	float						FovAngleY_;					// 
	float4						CamSize_;							// 
	float						NearZ_;								// 
	float						FarZ_;									// 

public:
	CameraComponent();
	~CameraComponent();

protected:		// delete constructer
	CameraComponent(const CameraComponent& _other) = delete;
	CameraComponent(CameraComponent&& _other) noexcept = delete;

private:		//delete operator
	CameraComponent& operator=(const CameraComponent& _other) = delete;
	CameraComponent& operator=(const CameraComponent&& _other) = delete;

private:
	void CameraTransformUpdate();

public:
	void SetProjectionMode(ProjectionMode _ProjectionMode);

protected:
	void Start() override;
	void Update() override;
};


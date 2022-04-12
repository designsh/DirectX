#pragma once
#include "GameEngineActor.h"
#include "CameraComponent.h"

// 분류 : 카메라 액터
// 용도 : 
// 설명 : 
class CameraActor : public GameEngineActor
{
private:	// member Var
	CameraComponent*		Camera_;				// 카메라 컴포넌트(실질적인 카메라역할수행)

private: // 프리카메라관련
	GameEngineTransform		OriginTransform;		// 프리카메라모드사용전 트랜스폼데이터(원본)
	float					FreeCameraSpeed_;		// 프리카메라모드에서의 카메라 이동속도
	float					RotSpeed_;				// 프리카메라모드에서의 카메라 회전각도
	bool					IsFreeCameraMode_;		// 프리카메라모드 사용유무 Flag
	ProjectionMode			PrevCamMode_;			// 프리카메라모드에서의 투영타입(원근투영)

public:
	CameraActor();
	~CameraActor();

protected:		// delete constructer
	CameraActor(const CameraActor& _other) = delete;
	CameraActor(CameraActor&& _other) noexcept = delete;

private:		//delete operator
	CameraActor& operator=(const CameraActor& _other) = delete;
	CameraActor& operator=(const CameraActor&& _other) = delete;

public:
	CameraComponent* GetCamera() const;

public:
	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);

public: // 프리카메라관련
	bool IsFreeCameraMode();
	void FreeCameraModeSwitch();
	void FreeCameraModeOn();
	void FreeCameraModeOff();
};


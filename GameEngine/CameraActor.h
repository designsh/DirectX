#pragma once
#include "GameEngineActor.h"

// �з� : ī�޶� ����
// �뵵 : 
// ���� : 
class CameraComponent;
class CameraActor : public GameEngineActor
{
private:	// member Var
	CameraComponent* Camera_;

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
	float4x4 GetPorjectionMatrix();

protected:
	virtual void Start();
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime);

};


#pragma once
#include "GameEngineActor.h"
#include "CameraComponent.h"

// �з� : ī�޶� ����
// �뵵 : 
// ���� : 
class CameraActor : public GameEngineActor
{
private:	// member Var
	CameraComponent*		Camera_;				// ī�޶� ������Ʈ(�������� ī�޶��Ҽ���)

private: // ����ī�޶����
	GameEngineTransform		OriginTransform;		// ����ī�޶������� Ʈ������������(����)
	float					FreeCameraSpeed_;		// ����ī�޶��忡���� ī�޶� �̵��ӵ�
	float					RotSpeed_;				// ����ī�޶��忡���� ī�޶� ȸ������
	bool					IsFreeCameraMode_;		// ����ī�޶��� ������� Flag
	ProjectionMode			PrevCamMode_;			// ����ī�޶��忡���� ����Ÿ��(��������)

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

public: // ����ī�޶����
	bool IsFreeCameraMode();
	void FreeCameraModeSwitch();
	void FreeCameraModeOn();
	void FreeCameraModeOff();
};


#include "PreCompile.h"
#include "CameraActor.h"
#include "CameraComponent.h"
#include "GameEngineTransform.h"
#include "GameEngineInput.h"

CameraActor::CameraActor() : 
	Camera_(nullptr),
	OriginTransform{},
	FreeCameraSpeed_(200.0f),
	RotSpeed_(360.0f),
	IsFreeCameraMode_(false),
	PrevCamMode_()
{
}

CameraActor::~CameraActor()
{
}

CameraComponent* CameraActor::GetCamera() const
{
	return Camera_;
}

float4x4 CameraActor::GetViewMatrix()
{
	return Camera_->GetTransform()->GetTransformData().View_;
}

float4x4 CameraActor::GetProjectionMatrix()
{
	return Camera_->GetTransform()->GetTransformData().Projection_;
}

void CameraActor::Start()
{
	// ī�޶� ������Ʈ ����
	Camera_ = CreateTransformComponent<CameraComponent>(GetTransform());

#pragma region ����ī�޶���� ����
	// ����ī�޶��忡���� ����Ÿ��(��������)
	PrevCamMode_ = Camera_->ProjectionMode_;

	// ����ī�޶��忡�� ����ϴ� Ű ���
	if (false == GameEngineInput::GetInst().IsKey("CAMMoveFoward"))
	{
		GameEngineInput::GetInst().CreateKey("CAMMoveFoward", 'W');
		GameEngineInput::GetInst().CreateKey("CAMMoveBack", 'S');
		GameEngineInput::GetInst().CreateKey("CAMMoveUp", 'Q');
		GameEngineInput::GetInst().CreateKey("CAMMoveDown", 'E');
		GameEngineInput::GetInst().CreateKey("CAMMoveLeft", 'A');
		GameEngineInput::GetInst().CreateKey("CAMMoveRight", 'D');
		GameEngineInput::GetInst().CreateKey("CAMSpeedBoost", VK_LSHIFT);
		GameEngineInput::GetInst().CreateKey("CAMRot", VK_RBUTTON);
	}
#pragma endregion
}

void CameraActor::Update(float _DeltaTime)
{
	// ����ī�޶��� �̻��� ����
	if (false == IsFreeCameraMode_)
	{
		return;
	}

#pragma region ����ī�޶���
	// �̵��ӵ�����
	float MoveSpeed = FreeCameraSpeed_;

	if (GameEngineInput::GetInst().Press("CAMSpeedBoost"))
	{
		MoveSpeed *= 3.0f;
	}

	if (GameEngineInput::GetInst().Press("CAMMoveFoward"))
	{
		GetTransform()->SetWorldMove(GetTransform()->GetWorldForwardVector() * _DeltaTime * MoveSpeed);
	}

	if (GameEngineInput::GetInst().Press("CAMMoveBack"))
	{
		GetTransform()->SetWorldMove(GetTransform()->GetWorldBackVector() * _DeltaTime * MoveSpeed);

	}

	if (GameEngineInput::GetInst().Press("CAMMoveUp"))
	{
		GetTransform()->SetWorldMove(GetTransform()->GetWorldUpVector() * _DeltaTime * MoveSpeed);

	}

	if (GameEngineInput::GetInst().Press("CAMMoveDown"))
	{
		GetTransform()->SetWorldMove(GetTransform()->GetWorldDownVector() * _DeltaTime * MoveSpeed);

	}

	if (GameEngineInput::GetInst().Press("CAMMoveLeft"))
	{
		GetTransform()->SetWorldMove(GetTransform()->GetWorldLeftVector() * _DeltaTime * MoveSpeed);
	}

	if (GameEngineInput::GetInst().Press("CAMMoveRight"))
	{
		GetTransform()->SetWorldMove(GetTransform()->GetWorldRightVector() * _DeltaTime * MoveSpeed);
	}

	if (GameEngineInput::GetInst().Press("CAMRot"))
	{
		GetTransform()->AddWorldRotationDegreeY(GameEngineInput::GetMouse3DDir().x * _DeltaTime * RotSpeed_);
		GetTransform()->AddWorldRotationDegreeX(-GameEngineInput::GetMouse3DDir().y * _DeltaTime * RotSpeed_);
	}
#pragma endregion
}

bool CameraActor::IsFreeCameraMode()
{
	return IsFreeCameraMode_;
}

void CameraActor::FreeCameraModeSwitch()
{
	// ����ī�޶� On/Off
	IsFreeCameraMode_ = !IsFreeCameraMode_;

	switch (IsFreeCameraMode_)
	{
		case true:
		{
			FreeCameraModeOn();
			break;
		}
		case false:
		{
			FreeCameraModeOff();
			break;
		}
	}
}

void CameraActor::FreeCameraModeOn()
{
	IsFreeCameraMode_ = true;

	// ��������Ÿ�� ���� �� ��������Ÿ������ ��ȯ
	PrevCamMode_ = Camera_->ProjectionMode_;
	Camera_->SetProjectionMode(ProjectionMode::Perspective);

	// ����� Ʈ������������ ����
	OriginTransform.Copy(*GetTransform());
}

void CameraActor::FreeCameraModeOff()
{
	IsFreeCameraMode_ = false;

	// ��������Ÿ������ ����
	Camera_->SetProjectionMode(PrevCamMode_);

	// ����ī�޶� ����� ������ Ʈ�����������ͷ� ����
	GetTransform()->Copy(OriginTransform);
}

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
	// 카메라 컴포넌트 생성
	Camera_ = CreateTransformComponent<CameraComponent>(GetTransform());

#pragma region 프리카메라관련 생성
	// 프리카메라모드에서의 투영타입(원근투영)
	PrevCamMode_ = Camera_->ProjectionMode_;

	// 프리카메라모드에서 사용하는 키 등록
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
	// 프리카메라모드 미사용시 리턴
	if (false == IsFreeCameraMode_)
	{
		return;
	}

#pragma region 프리카메라모드
	// 이동속도셋팅
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
	// 프리카메라 On/Off
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

	// 이전투영타입 저장 및 원근투영타입으로 변환
	PrevCamMode_ = Camera_->ProjectionMode_;
	Camera_->SetProjectionMode(ProjectionMode::Perspective);

	// 사용전 트랜스폼데이터 저장
	OriginTransform.Copy(*GetTransform());
}

void CameraActor::FreeCameraModeOff()
{
	IsFreeCameraMode_ = false;

	// 이전투영타입으로 원복
	Camera_->SetProjectionMode(PrevCamMode_);

	// 프리카메라 사용전 상태의 트랜스폼데이터로 원복
	GetTransform()->Copy(OriginTransform);
}

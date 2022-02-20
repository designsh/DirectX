#include "PreCompile.h"
#include "CameraComponent.h"
#include "GameEngineTransform.h"

#include "GameEngineWindow.h"

CameraComponent::CameraComponent() : 
	ProjectionMode_(ProjectionMode::Perspective), 
	FovAngleY_(90.0f),
	CamSize_(GameEngineWindow::GetInst().GetSize()),
	NearZ_(0.1f),
	FarZ_(1000.0f)
{
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::CameraTransformUpdate()
{
	GetTransform()->GetTransformData().View_.ViewToLH(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldForwardVector(), GetTransform()->GetWorldUpVector());

	switch (ProjectionMode_)
	{
		case ProjectionMode::Perspective:
		{
			GetTransform()->GetTransformData().Projection_.PerspectiveFovLH(FovAngleY_, CamSize_.x, CamSize_.y, NearZ_, FarZ_);
			break;
		}
		case ProjectionMode::Orthographic:
		{
			GetTransform()->GetTransformData().Projection_.OrthographicLH(CamSize_.x, CamSize_.y, NearZ_, FarZ_);
			break;
		}
	}
}

void CameraComponent::SetProjectionMode(ProjectionMode _ProjectionMode)
{
	ProjectionMode_ = _ProjectionMode;
}

void CameraComponent::Start()
{
}

void CameraComponent::Update()
{
}

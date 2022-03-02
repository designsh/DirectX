#pragma once
#include "GameEngineTransformComponent.h"

// ���� Ÿ��
enum class ProjectionMode
{
	Perspective,
	Orthographic
};

// �з� : ī�޶� ������Ʈ
// �뵵 : 
// ���� : 
class GameEngineRenderer;
class CameraComponent : public GameEngineTransformComponent
{
	friend class CameraActor;
	friend class GameEngineLevel;

private:	// member Var
	ProjectionMode	ProjectionMode_;			// 
	float						FovAngleY_;					// 
	float4						CamSize_;							// 
	float						NearZ_;								// 
	float						FarZ_;									// 

private:
	std::map<int, std::list<GameEngineRenderer*>> RendererList_;

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
	void Render();
	void ReleaseRenderer();

public:
	void SetProjectionMode(ProjectionMode _ProjectionMode);
	void PushRenderer(int _Order, GameEngineRenderer* _Renderer);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
};


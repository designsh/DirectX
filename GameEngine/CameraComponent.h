#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineDebugRenderData.h"
#include "Enums.h"

// 투영 타입
enum class ProjectionMode
{
	Perspective,
	Orthographic
};

// 분류 : 카메라 컴포넌트
// 용도 : 
// 설명 : 
class GameEngineRenderer;
class CameraComponent : public GameEngineTransformComponent
{
	friend class CameraActor;
	friend class GameEngineLevel;

private:	// member Var
	ProjectionMode				ProjectionMode_;			// 
	float						FovAngleY_;					// 
	float4						CamSize_;					// 
	float						NearZ_;						// 
	float						FarZ_;						// 

private:
	std::map<int, std::list<GameEngineRenderer*>> RendererList_;

private:
	std::vector<GameEngineDebugRenderData> DebugVector_;
	int DebugRenderCount_;

public:
	GameEngineRenderTarget* CameraBufferTarget_;

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
	inline GameEngineRenderTarget* GetCameraRenderTarget()
	{
		return CameraBufferTarget_;
	}

private:
	void ClearCameraTarget();
	void CameraTransformUpdate();
	void Render();
	void DebugRender();
	void ReleaseRenderer();

public:
	void SetProjectionMode(ProjectionMode _ProjectionMode);
	void PushRenderer(int _Order, GameEngineRenderer* _Renderer);

public:
	void PushDebugRender(GameEngineTransform* _Trans, CollisionType _Type);
	void ChangeRendererGroup(int _Group, GameEngineRenderer* _Renderer);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
};


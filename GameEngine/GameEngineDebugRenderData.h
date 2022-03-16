#pragma once
#include "GameEngineTransform.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// 분류 : 디버그 렌더 데이터
// 용도 : 디버그용 충돌체 메쉬 관리
// 설명 : 
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineDebugRenderData
{
	friend class CameraComponent;

private:	// member Var
	TransformData											Data_;
	float4																Color_;
	GameEngineShaderResHelper				ShaderHelper_;
	GameEngineRenderingPipeLine*			PipeLine_;

public:
	GameEngineDebugRenderData();
	~GameEngineDebugRenderData();

protected:		// delete constructer
	//GameEngineDebugRenderData(const GameEngineDebugRenderData& _other) = delete;
	//GameEngineDebugRenderData(GameEngineDebugRenderData&& _other) noexcept = delete;

private:		//delete operator
	//GameEngineDebugRenderData& operator=(const GameEngineDebugRenderData& _other) = delete;
	//GameEngineDebugRenderData& operator=(const GameEngineDebugRenderData&& _other) = delete;

public:
};


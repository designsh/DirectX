#pragma once
#include "GameEngineTexture.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineDepthBuffer : public GameEngineObjectNameBase
{
private:	// member Var
	GameEngineTexture* DepthTexture_;

public:
	GameEngineDepthBuffer();
	~GameEngineDepthBuffer();

protected:		// delete constructer
	GameEngineDepthBuffer(const GameEngineDepthBuffer& _other) = delete;
	GameEngineDepthBuffer(GameEngineDepthBuffer&& _other) noexcept = delete;

private:		//delete operator
	GameEngineDepthBuffer& operator=(const GameEngineDepthBuffer& _other) = delete;
	GameEngineDepthBuffer& operator=(const GameEngineDepthBuffer&& _other) = delete;

public:
	inline ID3D11DepthStencilView* GetDepthStencilView()
	{
		return DepthTexture_->GetDepthStencilView();
	}

public:
	void Create(float4 _Scale);
};


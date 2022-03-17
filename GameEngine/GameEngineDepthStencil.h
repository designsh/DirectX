#pragma once
#include <GameEngine/GameEngineDevice.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineDepthStencil : public GameEngineObjectNameBase
{
	friend class GameEngineDepthStencilManager;

private:	// member Var
	D3D11_DEPTH_STENCIL_DESC Info_;
	ID3D11DepthStencilState* State_;

public:
	GameEngineDepthStencil();
	~GameEngineDepthStencil();

protected:		// delete constructer
	GameEngineDepthStencil(const GameEngineDepthStencil& _other) = delete;
	GameEngineDepthStencil(GameEngineDepthStencil&& _other) noexcept = delete;

private:		//delete operator
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil& _other) = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil&& _other) = delete;

public:
	void ReCreate(const D3D11_DEPTH_STENCIL_DESC& _Info);

private:
	void Create(const D3D11_DEPTH_STENCIL_DESC& _Info);

public:
	void Setting();
	void Reset();
};


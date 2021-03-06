#pragma once
#include <GameEngineBase/GameEngineSoundManager.h>

#include "GameEngineConstantBufferManager.h"

#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"
#include "GameEnginePixelShaderManager.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineTextureManager.h"
#include "GameEngineSamplerManager.h"
#include "GameEngineBlendManager.h"
#include "GameEngineDepthStencilManager.h"
#include "GameEngineDepthBufferManager.h"
#include "GameEngineFontManager.h" 

#include "GameEngineRenderingPipeLineManager.h"

#include "GameEngineConstantBufferManager.h"

#include "GameEngineFont.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineBlend.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineDepthBuffer.h"

#include "GameEngineRenderingPipeLine.h"

#include "KeyboardClass.h"

class GameEngineManagerHelper
{
public:
	static void ManagerRelease()
	{
		GameEngineSoundManager::Destroy();
		GameEngineFontManager::Destroy();
		KeyboardClass::Destroy();

		GameEngineRenderingPipeLineManager::Destroy();

		GameEngineConstantBufferManager::Destroy();

		GameEngineIndexBufferManager::Destroy();
		GameEngineVertexBufferManager::Destroy();
		GameEngineVertexShaderManager::Destroy();
		GameEngineRasterizerManager::Destroy();
		GameEnginePixelShaderManager::Destroy();
		GameEngineRenderTargetManager::Destroy();
		GameEngineSamplerManager::Destroy();
		GameEngineFolderTextureManager::Destroy();
		GameEngineTextureManager::Destroy();
		GameEngineBlendManager::Destroy();
		GameEngineDepthStencilManager::Destroy();
		GameEngineDepthBufferManager::Destroy();
	}
};

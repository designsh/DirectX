#pragma once
#include <GameEngineBase/GameEngineSoundManager.h>
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"
#include "GameEngineTextureManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEngineTexture.h"

class GameEngineManagerHelper
{
public:
	static void ManagerRelease()
	{
		GameEngineIndexBufferManager::Destroy();
		GameEngineVertexShaderManager::Destroy();
		GameEngineVertexBufferManager::Destroy();
		GameEngineRasterizerManager::Destroy();
		GameEngineTextureManager::Destroy();
		GameEngineSoundManager::Destroy();
	}
};

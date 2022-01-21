#pragma once

#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineTextureManager.h"
#include "GameEngineRasterizerManager.h"

class GameEngineManagerHelper
{
public:
	// Resource Release
	static void ManagerRelease()
	{
		GameEngineIndexBufferManager::Destroy();
		GameEngineVertexShaderManager::Destroy();
		GameEngineVertexBufferManager::Destroy();
		GameEngineTextureManager::Destroy();
		GameEngineSoundManager::Destroy();
		GameEngineRasterizerManager::Destroy();
	}
};

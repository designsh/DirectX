#pragma once
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// 분류 : 디렉터리 텍스쳐
// 용도 : 
// 설명 : 디렉터리를 기준으로 텍스쳐를 로드하는 기능을 수행
class GameEngineTexture;
class GameEngineFolderTexture : public GameEngineObjectNameBase
{
private:	// member Var
	std::vector<GameEngineTexture*> AllTexture_;

public:
	GameEngineFolderTexture();
	~GameEngineFolderTexture();

protected:		// delete constructer
	GameEngineFolderTexture(const GameEngineFolderTexture& _other) = delete;
	GameEngineFolderTexture(GameEngineFolderTexture&& _other) noexcept = delete;

private:		//delete operator
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture& _other) = delete;
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture&& _other) = delete;

public:
	inline int GetTextureCount()
	{
		return static_cast<int>(AllTexture_.size());
	}

public:
	GameEngineTexture* GetTextureIndex(int _Index);

public:
	void Load(const std::string& _Path);
};


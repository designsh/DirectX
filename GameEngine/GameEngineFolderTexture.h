#pragma once
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// �з� : ���͸� �ؽ���
// �뵵 : 
// ���� : ���͸��� �������� �ؽ��ĸ� �ε��ϴ� ����� ����
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


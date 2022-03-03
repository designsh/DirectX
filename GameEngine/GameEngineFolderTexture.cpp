#include "PreCompile.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineTexture.h"

GameEngineFolderTexture::GameEngineFolderTexture()
{
}

GameEngineFolderTexture::~GameEngineFolderTexture()
{
	for (size_t i = 0; i < AllTexture_.size(); i++)
	{
		if (nullptr != AllTexture_[i])
		{
			delete AllTexture_[i];
			AllTexture_[i] = nullptr;
		}
	}
}

GameEngineTexture* GameEngineFolderTexture::GetTextureIndex(int _Index)
{
	return AllTexture_[_Index];
}

void GameEngineFolderTexture::Load(const std::string& _Path)
{
	GameEngineDirectory TextureDir = _Path;

	std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();
	for (size_t i = 0; i < AllFile.size(); i++)
	{
		GameEngineTexture* NewRes = new GameEngineTexture();
		NewRes->SetName(AllFile[i].GetFileName());
		NewRes->Load(AllFile[i].GetFullPath());
		AllTexture_.push_back(NewRes);
	}
}

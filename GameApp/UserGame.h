#pragma once
#include <GameEngine/GameEngineCore.h>

// 분류 : 
// 용도 : 
// 설명 : 
class TitleLevel;
class CreateCharactorLevel;
class SelectCharactorLevel;
class LoadingLevel;
class TownLevel;
class CatacombsLevel;
class ChaosSanctuaryLevel;
class UserGame : public GameEngineCore
{
private:	// member Var

public:
	UserGame();
	~UserGame();

protected:		// delete constructer
	UserGame(const UserGame& _other) = delete;
	UserGame(UserGame&& _other) noexcept = delete;

private:		//delete operator
	UserGame& operator=(const UserGame& _other) = delete;
	UserGame& operator=(const UserGame&& _other) = delete;

public:
	virtual void Initialize() override;
	virtual void ResourcesLoad() override;
	virtual void Release() override;
	virtual float4 StartWindowPos() override;
	virtual float4 StartWindowSize() override;
};


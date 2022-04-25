#pragma once
#include "Navigation_Common.h"
#include "Navigation.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTileMapRenderer;
class Navigation2D : public Navigation
{
private:	// member Var
	GameEngineTileMapRenderer* NavData_;
	NavInfoManager* NavInfoManager_;

public:
	Navigation2D();
	virtual ~Navigation2D();

protected:		// delete constructer
	Navigation2D(const Navigation2D& _other) = delete;
	Navigation2D(Navigation2D&& _other) noexcept = delete;

private:		//delete operator
	Navigation2D& operator=(const Navigation2D& _other) = delete;
	Navigation2D& operator=(const Navigation2D&& _other) = delete;

public:
	virtual bool FindPath(const float4& _Start, const float4& _Goal, std::vector<float4>& _vecPath) override;

public:
	inline GameEngineTileMapRenderer* GetTileMap() const
	{
		return NavData_;
	}

public:
	inline void SetNavData(GameEngineTileMapRenderer* _Data)
	{
		NavData_ = _Data;
	}

	inline void SetNavInfoManager(NavInfoManager* _Info)
	{
		NavInfoManager_ = _Info;
	}


};


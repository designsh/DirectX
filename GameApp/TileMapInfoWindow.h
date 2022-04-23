#pragma once
#include <GameEngine/GameEngineGUI.h>

// �з� : 
// �뵵 : 
// ���� : 
class TileMapInfoWindow : public GameEngineGUIWindow
{
private:	// member Var

public:
	TileMapInfoWindow();
	~TileMapInfoWindow();

protected:		// delete constructer
	TileMapInfoWindow(const TileMapInfoWindow& _other) = delete;
	TileMapInfoWindow(TileMapInfoWindow&& _other) noexcept = delete;

private:		//delete operator
	TileMapInfoWindow& operator=(const TileMapInfoWindow& _other) = delete;
	TileMapInfoWindow& operator=(const TileMapInfoWindow&& _other) = delete;

protected:
	virtual void OnGUI() override;

public:
};

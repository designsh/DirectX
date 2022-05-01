#pragma once
#include <GameEngine/GameEngineActor.h>

// 퀵슬롯 정보
struct QuickSlotInfo
{

};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_QuickSlot : public GameEngineActor
{
private:

private:
	QuickSlotInfo QuitSlotInfo_;

public:
	MainPlayer_QuickSlot();
	~MainPlayer_QuickSlot();

protected:		// delete constructer
	MainPlayer_QuickSlot(const MainPlayer_QuickSlot& _other) = delete;
	MainPlayer_QuickSlot(MainPlayer_QuickSlot&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_QuickSlot& operator=(const MainPlayer_QuickSlot& _other) = delete;
	MainPlayer_QuickSlot& operator=(const MainPlayer_QuickSlot&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
};


#pragma once
#include <GameEngine/GameEngineActor.h>

// ºÐ·ù : 
// ¿ëµµ : 
// ¼³¸í : 
class MainPlayer_QuickSlot : public GameEngineActor
{
private: // Äü½½·Ô ÀåÂø»óÅÂ

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


#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class NPC_TopMenuBar : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* TopMenuPanel_;

private:
	GameEngineUIRenderer* BuySellMenuRenderer_;
	GameEngineCollision* ButSellMenuCol_;

public:
	NPC_TopMenuBar();
	~NPC_TopMenuBar();

protected:		// delete constructer
	NPC_TopMenuBar(const NPC_TopMenuBar& _other) = delete;
	NPC_TopMenuBar(NPC_TopMenuBar&& _other) noexcept = delete;

private:		//delete operator
	NPC_TopMenuBar& operator=(const NPC_TopMenuBar& _other) = delete;
	NPC_TopMenuBar& operator=(const NPC_TopMenuBar&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


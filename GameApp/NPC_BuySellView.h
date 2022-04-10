#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class NPC_BuySellView : public GameEngineActor
{
private:	// member Var


public:
	NPC_BuySellView();
	~NPC_BuySellView();

protected:		// delete constructer
	NPC_BuySellView(const NPC_BuySellView& _other) = delete;
	NPC_BuySellView(NPC_BuySellView&& _other) noexcept = delete;

private:		//delete operator
	NPC_BuySellView& operator=(const NPC_BuySellView& _other) = delete;
	NPC_BuySellView& operator=(const NPC_BuySellView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


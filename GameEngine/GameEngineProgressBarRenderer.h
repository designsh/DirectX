#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineProgressBarRenderer
{
private:	// member Var

public:
	GameEngineProgressBarRenderer();
	~GameEngineProgressBarRenderer();

protected:		// delete constructer
	GameEngineProgressBarRenderer(const GameEngineProgressBarRenderer& _other) = delete;
	GameEngineProgressBarRenderer(GameEngineProgressBarRenderer&& _other) noexcept = delete;

private:		//delete operator
	GameEngineProgressBarRenderer& operator=(const GameEngineProgressBarRenderer& _other) = delete;
	GameEngineProgressBarRenderer& operator=(const GameEngineProgressBarRenderer&& _other) = delete;

public:
};


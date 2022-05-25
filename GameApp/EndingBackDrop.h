#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class EndingBackDrop : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* BackDrop_;

public:
	EndingBackDrop();
	~EndingBackDrop();

protected:		// delete constructer
	EndingBackDrop(const EndingBackDrop& _other) = delete;
	EndingBackDrop(EndingBackDrop&& _other) noexcept = delete;

private:		//delete operator
	EndingBackDrop& operator=(const EndingBackDrop& _other) = delete;
	EndingBackDrop& operator=(const EndingBackDrop&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


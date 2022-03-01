#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �̹���
// �뵵 : Ÿ��Ʋ���� ���
// ���� : 
class GameEngineImageRenderer;
class TitleBackDrop : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* BackDrop_;

public:
	TitleBackDrop();
	~TitleBackDrop();

protected:		// delete constructer
	TitleBackDrop(const TitleBackDrop& _other) = delete;
	TitleBackDrop(TitleBackDrop&& _other) noexcept = delete;

private:		//delete operator
	TitleBackDrop& operator=(const TitleBackDrop& _other) = delete;
	TitleBackDrop& operator=(const TitleBackDrop&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};


#pragma once
#include <GameEngine/GameEngineGUI.h>

// �з� : 
// �뵵 : 
// ���� : 
class CreateRandomMapWindow : public GameEngineGUIWindow
{
private:	// member Var

public:
	CreateRandomMapWindow();
	~CreateRandomMapWindow();

protected:		// delete constructer
	CreateRandomMapWindow(const CreateRandomMapWindow& _other) = delete;
	CreateRandomMapWindow(CreateRandomMapWindow&& _other) noexcept = delete;

private:		//delete operator
	CreateRandomMapWindow& operator=(const CreateRandomMapWindow& _other) = delete;
	CreateRandomMapWindow& operator=(const CreateRandomMapWindow&& _other) = delete;

protected:
	virtual void OnGUI() override;

public:
};


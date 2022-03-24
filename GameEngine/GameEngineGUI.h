#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineGUI
{
private:
	static GameEngineGUI* Inst;

public:
	inline static GameEngineGUI* GetInst()
	{
		return Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var

public:
	GameEngineGUI();
	~GameEngineGUI();

protected:		// delete constructer
	GameEngineGUI(const GameEngineGUI& _other) = delete;
	GameEngineGUI(GameEngineGUI&& _other) noexcept = delete;

private:		//delete operator
	GameEngineGUI& operator=(const GameEngineGUI& _other) = delete;
	GameEngineGUI& operator=(const GameEngineGUI&& _other) = delete;

public:
	void Initialize();
	void GUIRenderStart();
	void GUIRenderEnd();
};


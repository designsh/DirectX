#pragma once
#include "imgui.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineGUIWindow;
class GameEngineGUI
{
	friend class GameEngineCore;
	friend class GameEngineLevel;

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
	std::map<std::string, GameEngineGUIWindow*> Windows_;

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

public:
	GameEngineGUIWindow* FindGUIWindow(const std::string& _Name)
	{
		std::map<std::string, GameEngineGUIWindow*>::iterator FindIter = Windows_.find(_Name);

		if (FindIter == Windows_.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

public:
	template<typename WindowType>
	WindowType* CreateGUIWindow(const std::string& _Name)
	{
		WindowType* NewWindow = new WindowType();

		NewWindow->SetName(_Name);

		Windows_.insert(std::map<std::string, GameEngineGUIWindow*>::value_type(_Name, NewWindow));

		return NewWindow;
	}
};

class GameEngineGUIWindow : public GameEngineObjectNameBase
{
	friend class GameEngineGUI;

private:	// member Var

public:
	GameEngineGUIWindow();
	~GameEngineGUIWindow();

protected:		// delete constructer
	GameEngineGUIWindow(const GameEngineGUIWindow& _other) = delete;
	GameEngineGUIWindow(GameEngineGUIWindow&& _other) noexcept = delete;

private:		//delete operator
	GameEngineGUIWindow& operator=(const GameEngineGUIWindow& _other) = delete;
	GameEngineGUIWindow& operator=(const GameEngineGUIWindow&& _other) = delete;

public:
	void Begin()
	{
		ImGui::Begin(GetName().c_str(), &GetIsUpdateRef());
	}

	virtual void OnGUI() = 0;

	void End()
	{
		ImGui::End();
	}
};

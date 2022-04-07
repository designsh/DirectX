#pragma once
#include "imgui.h"

// �з� : 
// �뵵 : 
// ���� : 
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
	std::list<GameEngineGUIWindow*> Windows_;

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
	std::list<GameEngineGUIWindow*> FindGUIWindowForList(const std::string& _Name);

	GameEngineGUIWindow* FindGUIWindow(const std::string& _Name)
	{
		return FindGUIWindow<GameEngineGUIWindow>(_Name);
	}

	template<typename Convert>
	Convert* FindGUIWindow(const std::string& _Name)
	{
		for (auto FindIter : Windows_)
		{
			if (FindIter->GetName() == _Name)
			{
				return dynamic_cast<Convert*>(FindIter);
			}
		}

		return nullptr;
	}

public:
	template<typename WindowType>
	WindowType* CreateGUIWindow(const std::string& _Name)
	{
		WindowType* NewWindow = new WindowType();

		NewWindow->SetName(_Name);

		Windows_.push_back(NewWindow);

		return NewWindow;
	}
};

class GameEngineGUIWindow : public GameEngineObjectNameBase
{
	friend class GameEngineGUI;

private:	// member Var
	GameEngineLevel* Level_;

public:
	inline void SetLevel(GameEngineLevel* _Level) 
	{
		Level_ = _Level;
	}

protected:
	int Style_;

public:
	GameEngineGUIWindow();
	~GameEngineGUIWindow();

private:
	GameEngineGUIWindow(const GameEngineGUIWindow& _other) = delete;
	GameEngineGUIWindow(GameEngineGUIWindow&& _other) noexcept = delete;

private:
	GameEngineGUIWindow& operator=(const GameEngineGUIWindow& _other) = delete;
	GameEngineGUIWindow& operator=(const GameEngineGUIWindow&& _other) = delete;

public:
	void Begin()
	{
		ImGui::Begin(GetName().c_str(), &GetIsUpdateRef(), Style_);
	}

	virtual void OnGUI() = 0;

	void End()
	{
		ImGui::End();
	}

public:
	virtual void Start()
	{

	}
};

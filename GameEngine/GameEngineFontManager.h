#pragma once

class GameEngineFont;
class GameEngineFontManager
{
private:
	static GameEngineFontManager* Inst;

public:
	static GameEngineFontManager& GetInst()
	{
		return *Inst;
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
	std::map<std::string, GameEngineFont*> ResourcesMap;

public:
	GameEngineFont* Load(const std::string& _Path);
	GameEngineFont* Find(const std::string& _Name);

private:
	GameEngineFontManager();
	~GameEngineFontManager();

protected:		// delete constructer
	GameEngineFontManager(const GameEngineFontManager& _other) = delete;
	GameEngineFontManager(GameEngineFontManager&& _other) noexcept;

private:		//delete operator
	GameEngineFontManager& operator=(const GameEngineFontManager& _other) = delete;
	GameEngineFontManager& operator=(const GameEngineFontManager&& _other) = delete;

public:

};





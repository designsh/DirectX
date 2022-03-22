#pragma once
#include <functional>
#include <map>

// Ό³Έν :
class GameEngineFSM
{
private:
	class State
	{
	public:
		std::string Name_;
		std::function<void()> Start_;
		std::function<void()> Update_;
		std::function<void()> End_;

		State(std::string _Name, std::function<void()> _Start, std::function<void()> _Update, std::function<void()> _End)
			: Name_(_Name),
			Start_(_Start),
			Update_(_Update),
			End_(_End)
		{
		}
	};


public:
	// constrcuter destructer
	GameEngineFSM();
	~GameEngineFSM();

	// delete Function
	GameEngineFSM(const GameEngineFSM& _Other) = delete;
	GameEngineFSM(GameEngineFSM&& _Other) noexcept = delete;
	GameEngineFSM& operator=(const GameEngineFSM& _Other) = delete;
	GameEngineFSM& operator=(GameEngineFSM&& _Other) noexcept = delete;

	void CreateState(const std::string& _Name, std::function<void()> _Update, std::function<void()> _Start = nullptr, std::function<void()> _EndStart = nullptr, std::function<void()> _Init = nullptr);
	void ChangeState(const std::string& _Name);

	inline bool IsCurrentState(const std::string& _Name) const
	{
		return Current_->Name_ == _Name;
	}

	inline std::string GetCurStateName() const
	{
		return Current_->Name_;
	}

	void Update();

protected:

private:
	std::map<std::string, State*> AllState_;

	State* Current_;
	State* Next_;
};

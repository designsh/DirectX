#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

class StateInfo
{
public:
	std::string _NextState;
	float Time;

public:
	StateInfo()
		: _NextState("")
		, Time(0.0f)
	{

	}

	StateInfo(const char* _Name)
		: _NextState(_Name)
		, Time(0.0f)
	{

	}

	StateInfo(const char* _Name, float _NextTime)
		: _NextState(_Name)
		, Time(_NextTime)
	{

	}



	StateInfo(const std::string& _Name)
		: _NextState(_Name)
		, Time(0.0f)
	{

	}

	StateInfo(const std::string& _Name, float _NextTime)
		: _NextState(_Name)
		, Time(_NextTime)
	{

	}

};

// �з� : FSM
// �뵵 : ���º� ó��
// ���� : ���º��� ȣ��Ǵ� �Լ��� �ش� ���¸��� ������ ó���� �� �ִ�.
template<typename FSMType>
class GameEngineFSM
{
	class State : public GameEngineObjectNameBase
	{
		friend class GameEngineFSM;

	public:
		GameEngineFSM* parent_;

		float StateTime;
		StateInfo(FSMType::* StateStart)(StateInfo _Ptr);
		StateInfo(FSMType::* StateUpdate)(StateInfo _Ptr);

	public:

		void CallStart()
		{
#ifdef _DEBUG
			if (nullptr == parent_->ObjectPtr_)
			{
				GameEngineDebug::AssertFalse();
				return;
			}
#endif // _DEBUG
			(parent_->ObjectPtr_->*StateStart)({ GetName(), 0.0f });
			StateTime = 0.0f;
		}

		void CallUpdate()
		{
#ifdef _DEBUG
			if (nullptr == parent_->ObjectPtr_)
			{
				GameEngineDebug::AssertFalse();
				return;
			}
#endif // _DEBUG

			StateTime += GameEngineTime::GetInst().GetDeltaTime();
			StateInfo Return = (parent_->ObjectPtr_->*StateUpdate)({ GetName(), StateTime });

			if (Return._NextState.size() == 0)
			{
				return;
			}

			if (Return._NextState == "")
			{
				return;
			}
#ifdef _DEBUG
			if (nullptr == parent_->FindState(Return._NextState))
			{
				GameEngineDebug::AssertFalse();
			}
#endif // _DEBUG
			// �Ѿ�� �ִ°��ε�.
			if (0 >= Return.Time)
			{
				parent_->ChangeState(Return._NextState);
			}

			// �Ѿ�µ� ���ʸ� ��ٷ��� �ȴٴ°��� �˰� �Ǿ���.
			parent_->nextState_ = Return;
		}

	public:
		void Update() {}

	public:
		State(GameEngineFSM* _parent)
			: parent_(_parent)
			, StateStart(nullptr)
			, StateUpdate(nullptr)
			, StateTime(0.0f)
		{

		}
	};

private:
	std::map<std::string, State*> allState_;
	FSMType* ObjectPtr_;
	State* curState_;
	StateInfo nextState_;

private:	// member Var

public:
	friend State;

public:
	GameEngineFSM(FSMType* _StateObject)
		: curState_(nullptr)
		, ObjectPtr_(_StateObject)
	{
	}// default constructer ����Ʈ ������

	~GameEngineFSM()
	{
		typename std::map<std::string, State*>::iterator Start = allState_.begin();
		typename std::map<std::string, State*>::iterator End = allState_.end();

		for (; Start != End; ++Start)
		{
			delete Start->second;
		}
		allState_.clear();
	}// default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineFSM(const GameEngineFSM& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineFSM(GameEngineFSM&& _other) noexcept
	{
	}// default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineFSM& operator=(const GameEngineFSM& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineFSM& operator=(const GameEngineFSM&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����



public:
	void CreateState(const std::string& _name, StateInfo(FSMType::* _StartFunc)(StateInfo), StateInfo(FSMType::* _UpdateFunc)(StateInfo))
	{
#ifdef _DEBUG
		if (nullptr != FindState(_name))
		{
			GameEngineDebug::AssertFalse();
		}
#endif // _DEBUG

		State* NewState = new State(this);
		NewState->SetName(_name);

		NewState->StateUpdate = _UpdateFunc;
		NewState->StateStart = _StartFunc;
		allState_.insert(std::map<std::string, State*>::value_type(_name, NewState));
		return;
	}

	void ChangeState(const std::string& _Name)
	{
		curState_ = FindState(_Name);
#ifdef _DEBUG
		if (nullptr == curState_)
		{
			GameEngineDebug::AssertFalse();
			return;
		}
#endif // _DEBUG

		curState_->CallStart();
	}

	bool IsCurStateName(const std::string& _Name)
	{
		if (nullptr == curState_)
		{
			GameEngineDebug::AssertFalse();
			return false;
		}

		if (curState_->GetName() == _Name)
		{
			return true;
		}

		return false;
	}

private:
	State* FindState(const std::string& _name)
	{
		typename std::map<std::string, State*>::iterator FindAniIter = allState_.find(_name);

		if (FindAniIter == allState_.end())
		{
			return nullptr;
		}

		return FindAniIter->second;
	}


public:
	void Update()
	{
#ifdef _DEBUG
		if (nullptr == curState_)
		{
			GameEngineDebug::AssertFalse();
			return;
		}
#endif

		curState_->CallUpdate();
	}
};


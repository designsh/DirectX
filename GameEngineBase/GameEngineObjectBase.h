#pragma once
// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineObjectBase
{
private:	// member Var
	// true라고 하는순간 메모리적으로 파괴될겁니다.
	bool isDeath_;
	bool isUpdate_;
	bool isDebug_; // 디버깅 기능 이거 true로 해놓고 f9 걸어 놓으면 
	GameEngineObjectBase* parent_;

public:
	void SetParent(GameEngineObjectBase* _parent)
	{
		parent_ = _parent;
	}

public:
	bool IsDeath()
	{
		if (nullptr == parent_)
		{
			return isDeath_;
		}

		return true == isDeath_ || parent_->isDeath_;
	}

	bool IsOn()
	{
		if (nullptr == parent_)
		{
			return isUpdate_;
		}

		return true == isUpdate_ && parent_->isUpdate_;
	}


	void Death()
	{
		isDeath_ = true;
	}

	void On()
	{
		isUpdate_ = true;
	}

	void Off()
	{
		isUpdate_ = false;
	}

	void DebugOn()
	{
		isDebug_ = true;
	}

	void DebugOff()
	{
		isDebug_ = false;
	}

	void IsDebugCheck()
	{
		if (true == isDebug_)
		{
			int a = 0;
		}
	}

public:
	GameEngineObjectBase(); // default constructer 디폴트 생성자
	virtual ~GameEngineObjectBase(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineObjectBase(const GameEngineObjectBase& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineObjectBase& operator=(const GameEngineObjectBase&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};


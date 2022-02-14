#pragma once

// 분류 : 액터
// 용도 : 
// 설명 : 모든 물체에 대한 기능을 제공하고 갱신, 렌더링 기능을 제공
class GameEngineLevel;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

private:	// member Var
	GameEngineLevel* Level_;		// 본인이 속한 레벨을 알고있는다.

public:
	GameEngineActor(); // default constructer 디폴트 생성자
	~GameEngineActor(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineActor(const GameEngineActor& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineActor(GameEngineActor&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineActor& operator=(const GameEngineActor& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	virtual void Update(float _DeltaTime);

public:
	GameEngineLevel* GetLevel() const;
	void SetLevel(GameEngineLevel* Level);
};


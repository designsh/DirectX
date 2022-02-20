#pragma once

// 분류 : 액터
// 용도 : 
// 설명 : 모든 물체에 대한 기능을 제공하고 갱신, 렌더링 기능을 제공
class GameEngineLevel;
class GameEngineComponent;
class GameEngineTransformComponent;
class GameEngineTransform;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

private:	// member Var
	GameEngineLevel*															Level_;													// 본인이 속한 레벨을 알고있는다.
	GameEngineTransform*													Transform_;											// 액터는 반드시 트랜스폼데이터를 가진다.

private:
	std::list<GameEngineComponent*>								ComponentList_;								// 액터는 Transform을 가지지않는 여러개의 컴포넌트를 가질수 있다.
	std::list<GameEngineTransformComponent*>			TransformComponentList_;			// 액터는 Transform을 가지는 여러개의 컴포넌트를 가질수 있다.

public:
	GameEngineActor(); // default constructer 디폴트 생성자
	~GameEngineActor(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineActor(const GameEngineActor& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineActor(GameEngineActor&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineActor& operator=(const GameEngineActor& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	GameEngineLevel* GetLevel() const;
	GameEngineTransform* GetTransform();
	void SetLevel(GameEngineLevel* Level);

public: // 컴포넌트 생성
	template<typename ComponentType>
	ComponentType* CreateComponent(int _Order = 0)
	{
		// 해당 컴포넌트는 Transform을 가지지 않는 컴포넌트
		// Ex) 무기의 상태값과 같이 위치정보가 필요없는 컴포넌트
		GameEngineComponent* NewComponent = new ComponentType();
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		ComponentList_.push_back(NewComponent);

		// 컴포넌트의 세팅이 끝난뒤 Start() 호출
		NewComponent->Start();

		return dynamic_cast<ComponentType*>(NewComponent);;
	}

	template<typename ComponentType>
	ComponentType* CreateTransformComponent(GameEngineTransform* _ParentTrans, int _Order = 0)
	{
		// 업캐스팅을 이용해서 컴파일 에러를 낼것이다.
		GameEngineTransformComponent* NewComponent = new ComponentType();
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		if (nullptr == _ParentTrans)
		{
			GameEngineDebug::MsgBoxError("트랜스폼을 세팅안 해줬습니다.");
		}
		NewComponent->AttachTransform(_ParentTrans);
		ComponentList_.push_back(NewComponent);

		NewComponent->Start();

		return dynamic_cast<ComponentType*>(NewComponent);;
	}

protected:
	virtual void Start() {}
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime) {}

public:
	void UpdateComponent();
};


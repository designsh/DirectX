#pragma once

// �з� : ����
// �뵵 : 
// ���� : ��� ��ü�� ���� ����� �����ϰ� ����, ������ ����� ����
class GameEngineLevel;
class GameEngineComponent;
class GameEngineTransformComponent;
class GameEngineTransform;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

private:	// member Var
	GameEngineLevel*															Level_;													// ������ ���� ������ �˰��ִ´�.
	GameEngineTransform*													Transform_;											// ���ʹ� �ݵ�� Ʈ�����������͸� ������.

private:
	std::list<GameEngineComponent*>								ComponentList_;								// ���ʹ� Transform�� �������ʴ� �������� ������Ʈ�� ������ �ִ�.
	std::list<GameEngineTransformComponent*>			TransformComponentList_;			// ���ʹ� Transform�� ������ �������� ������Ʈ�� ������ �ִ�.

private:
	bool																						IsDestroyed_;										// �������� �����Ǵ� ���Ͱ� �����ϴ��� �Ǵ��ϴ� Flag
	float																						DeathTime_;										// n�ʵ� �ش� ���͸� �����ų�� ���

public:
	GameEngineActor(); // default constructer ����Ʈ ������
	~GameEngineActor(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineActor(const GameEngineActor& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineActor(GameEngineActor&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineActor& operator=(const GameEngineActor& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineActor& operator=(const GameEngineActor&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	GameEngineLevel* GetLevel() const;
	GameEngineTransform* GetTransform();

public:
	void SetLevel(GameEngineLevel* Level);

public: // ������Ʈ ����
	template<typename ComponentType>
	ComponentType* CreateComponent(int _Order = 0)
	{
		// �ش� ������Ʈ�� Transform�� ������ �ʴ� ������Ʈ
		// Ex) ������ ���°��� ���� ��ġ������ �ʿ���� ������Ʈ
		GameEngineComponent* NewComponent = new ComponentType();
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		ComponentList_.push_back(NewComponent);

		// ������Ʈ�� ������ ������ Start() ȣ��
		NewComponent->Start();

		return dynamic_cast<ComponentType*>(NewComponent);;
	}

	template<typename ComponentType>
	ComponentType* CreateTransformComponent(int _Order = 0)
	{
		// ��ĳ������ �̿��ؼ� ������ ������ �����̴�.
		GameEngineTransformComponent* NewComponent = new ComponentType();
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		NewComponent->AttachTransform(GetTransform());
		TransformComponentList_.push_back(NewComponent);

		NewComponent->Start();

		return dynamic_cast<ComponentType*>(NewComponent);;
	}

	template<typename ComponentType>
	ComponentType* CreateTransformComponent(GameEngineTransform* _ParentTrans, int _Order = 0)
	{
		// ��ĳ������ �̿��ؼ� ������ ������ �����̴�.
		GameEngineTransformComponent* NewComponent = new ComponentType();
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		if (nullptr == _ParentTrans)
		{
			GameEngineDebug::MsgBoxError("Ʈ�������� ���þ� ������ϴ�.");
		}
		NewComponent->AttachTransform(_ParentTrans);
		TransformComponentList_.push_back(NewComponent);

		NewComponent->Start();

		return dynamic_cast<ComponentType*>(NewComponent);;
	}

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void ReleaseEvent() {}

public:
	void UpdateComponent(float _DeltaTime);
	void ComponentRelease();
	void Release(float _Time = 0.0f);
	void ReleaseUpdate(float _DeltaTime);
};


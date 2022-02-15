#pragma once

// �з� : ����
// �뵵 : 
// ���� : ��� ��ü�� ���� ����� �����ϰ� ����, ������ ����� ����
class GameEngineLevel;
class GameEngineComponent;
class GameEngineTransform;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

private:	// member Var
	GameEngineLevel*									Level_;							// ������ ���� ������ �˰��ִ´�.
	GameEngineTransform*							Transform_;					// ���ʹ� �ݵ�� Ʈ�����������͸� ������.
	std::list<GameEngineComponent*>		ComponentList_;		// ���ʹ� �������� ������Ʈ�� ������ �ִ�.

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
	void SetLevel(GameEngineLevel* Level);

public: // ������Ʈ ����
	template<typename ComponentType>
	ComponentType* CreateComponent()
	{
		ComponentType* NewComponent = new ComponentType();
		NewComponent->InitComponent(this);

		ComponentList_.push_back(NewComponent);
	}

protected:
	virtual void Start() = 0;
	virtual void Update(float _DeltaTime) = 0;
};


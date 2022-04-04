#pragma once
#include <GameEngine/GameEngineActor.h>

enum class MouseState
{
	Move,
	Stay
};

// �з� : ���콺
// �뵵 : �ΰ��� ���콺
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MouseObject : public GameEngineActor
{
private:	// member Var
	bool IsItemHold_;
	std::string HoldItemName_;

private:
	GameEngineUIRenderer* ItemRenderer_;

private:
	GameEngineUIRenderer* Mouse_;
	GameEngineCollision* MouseCollider_;

private:
	MouseState State_;

public:
	MouseObject();
	~MouseObject();

protected:		// delete constructer
	MouseObject(const MouseObject& _other) = delete;
	MouseObject(MouseObject&& _other) noexcept = delete;

private:		//delete operator
	MouseObject& operator=(const MouseObject& _other) = delete;
	MouseObject& operator=(const MouseObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	bool IsItemHold() const	// �������� ����ִ��� üũ�ϴ� Flag
	{
		return IsItemHold_;
	}

	std::string GetHoldItemName() const
	{
		// �������� ����־������ �������̸��� �Ѱ��ټ� �ִ�.
		if (true == IsItemHold_)
		{
			return HoldItemName_;
		}

		return "";
	}

public:
	void ItemHold(const std::string& _ItemName, const float4& _ItemSize);
	void ItemPutDown();
};


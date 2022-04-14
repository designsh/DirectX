#pragma once
#include <GameEngine/GameEngineActor.h>

enum class MouseState
{
	Move,		// 이동
	Stay,		// 대기
	Buy,		// 구매버튼클릭으로 인한 구매기능 활성화
	Sell,		// 판매버튼클릭으로 인한 판매기능 활성화
	Repair,		// 수리버튼클릭으로 인한 수리기능 활성화
	Portal		// 포탈스크롤 사용시 포탈소환 기능활성화
};

// 분류 : 마우스
// 용도 : 인게임 마우스
// 설명 : 
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

public: // 마우스 상태 Get
	MouseState GetMouseState() const
	{
		return State_;
	}

public:
	bool IsItemHold() const	// 아이템을 들고있는지 체크하는 Flag
	{
		return IsItemHold_;
	}

	std::string GetHoldItemName() const
	{
		// 아이템을 들고있어야지만 아이템이름을 넘겨줄수 있다.
		if (true == IsItemHold_)
		{
			return HoldItemName_;
		}

		return "";
	}

public: // 아이템들기관련
	void ItemHold(const std::string& _ItemName, const float4& _ItemSize);
	void ItemPutDown();

public: // 특수기능에 따른 렌더러 변경관련
	void BuyCursorActive();
	void BuyCursorInActive();
	void SellCursorActive();
	void SellCursorInactive();
	void RepairCursorActive();
	void RepairCursorInactive();

public:
	void SpecialCursorProcess();
};


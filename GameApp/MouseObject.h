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
private: // 플레이어 UI 충돌체크
	bool PlayerUI_BottomStateBarCol_;
	bool PlayerUI_StatViewCol_;
	bool PlayerUI_SkillViewCol_;
	bool PlayerUI_IventoryViewCol_;
	bool PlayerUI_LWeaponSkillListBtnCol_;
	bool PlayerUI_RWeaponSkillListBtnCol_;
	bool PlayerUI_StoreViewCol_;

private: // NPC UI 충돌체크
	bool NPCUI_TopMenuBarCol_;
	bool NPCUI_BuySellViewCol_;

private: // 팝업창 충돌체크
	bool UI_PopupCol_;

private:
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
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

private:
	void MouseUICollision(GameEngineCollision* _Other);
	void MouseUICollisionEnd(GameEngineCollision* _Other);

private:
	void PopupUICollision(GameEngineCollision* _Other);
	void PopupUICollisionEnd(GameEngineCollision* _Other);

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

public:
	// 하단상태바의 UI선택중 이동체크 불가
	inline bool GetBottomStateBarCollision() const
	{
		return PlayerUI_BottomStateBarCol_;
	}

	// 화면의 오른쪽으로 이동체크 불가(스킬창 or 인벤토리창)
	inline bool GetScreenRightUIViewCollision() const
	{
		if (true == PlayerUI_SkillViewCol_)
		{
			return true;
		}

		if (true == PlayerUI_IventoryViewCol_)
		{
			return true;
		}

		return false;
	}

	// 화면의 왼쪽으로 이동체크 불가(스탯창 or 창고창)
	inline bool GetScreenLeftUIViewCollision() const
	{
		if (true == PlayerUI_StatViewCol_)
		{
			return true;
		}


		if (true == PlayerUI_StoreViewCol_)
		{
			return true;
		}

		return false;
	}

	// 왼쪽스킬리스트에서 스킬선택중 이동체크 불가
	inline bool GetLWeaponSkillListCollision() const
	{
		return PlayerUI_LWeaponSkillListBtnCol_;
	}

	// 오른쪽스킬리스트에서 스킬선택중 이동체크 불가
	inline bool GetRWeaponSkillListCollision() const
	{
		return PlayerUI_RWeaponSkillListBtnCol_;
	}

public: // NPC UI 체크 FLAG
	inline bool GetTopMenuBarCollision() const
	{
		return NPCUI_TopMenuBarCol_;
	}

	inline bool GetBuySellViewCollision() const
	{
		return NPCUI_BuySellViewCol_;
	}

public: // UI 팝업창 체크 Flag
	inline bool GetUIPopupCollision() const
	{
		return UI_PopupCol_;
	}

	inline void UIPopupCollisionOff()
	{
		UI_PopupCol_ = false;
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

public: // 마우스상태를 기본상태로 변경
	void CursorStateReset();
};


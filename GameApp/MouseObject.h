#pragma once
#include <GameEngine/GameEngineActor.h>

enum class MouseState
{
	Move,		// �̵�
	Stay,		// ���
	Buy,		// ���Ź�ưŬ������ ���� ���ű�� Ȱ��ȭ
	Sell,		// �ǸŹ�ưŬ������ ���� �Ǹű�� Ȱ��ȭ
	Repair,		// ������ưŬ������ ���� ������� Ȱ��ȭ
	Portal		// ��Ż��ũ�� ���� ��Ż��ȯ ���Ȱ��ȭ
};

// �з� : ���콺
// �뵵 : �ΰ��� ���콺
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MouseObject : public GameEngineActor
{
private: // �÷��̾� UI �浹üũ
	bool PlayerUI_BottomStateBarCol_;
	bool PlayerUI_StatViewCol_;
	bool PlayerUI_SkillViewCol_;
	bool PlayerUI_IventoryViewCol_;
	bool PlayerUI_LWeaponSkillListBtnCol_;
	bool PlayerUI_RWeaponSkillListBtnCol_;

private: // NPC UI �浹üũ
	bool NPCUI_TopMenuBarCol_;
	bool NPCUI_BuySellViewCol_;

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

public: // ���콺 ���� Get
	MouseState GetMouseState() const
	{
		return State_;
	}

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
	// �ϴܻ��¹��� UI������ �̵�üũ �Ұ�
	inline bool GetBottomStateBarCollision() const
	{
		return PlayerUI_BottomStateBarCol_;
	}

	// ȭ���� ���������� �̵�üũ �Ұ�
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

	// ȭ���� �������� �̵�üũ �Ұ�
	inline bool GetScreenLeftUIViewCollision() const
	{
		return PlayerUI_StatViewCol_;
	}

	// ���ʽ�ų����Ʈ���� ��ų������ �̵�üũ �Ұ�
	inline bool GetLWeaponSkillListCollision() const
	{
		return PlayerUI_LWeaponSkillListBtnCol_;
	}

	// �����ʽ�ų����Ʈ���� ��ų������ �̵�üũ �Ұ�
	inline bool GetRWeaponSkillListCollision() const
	{
		return PlayerUI_RWeaponSkillListBtnCol_;
	}

public: // NPC UI üũ FLAG
	inline bool GetTopMenuBarCollision() const
	{
		return NPCUI_TopMenuBarCol_;
	}

	inline bool GetBuySellViewCollision() const
	{
		return NPCUI_BuySellViewCol_;
	}

public: // �����۵�����
	void ItemHold(const std::string& _ItemName, const float4& _ItemSize);
	void ItemPutDown();

public: // Ư����ɿ� ���� ������ �������
	void BuyCursorActive();
	void BuyCursorInActive();
	void SellCursorActive();
	void SellCursorInactive();
	void RepairCursorActive();
	void RepairCursorInactive();

public: // ���콺���¸� �⺻���·� ����
	void CursorStateReset();
};


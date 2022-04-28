#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// â�� Ÿ��
enum class TakeInOutPopupType
{
	NONE = -1,		// ������ �ʱ�ȭ��
	TakeIn,			// �ֱ�
	TakeOut,		// ������
};

// â�� ������ ��ü�� Ÿ��
enum class TakeInOutPopCreateType
{
	NONE = -1,		// ������ �ʱ�ȭ��
	STOREDVIEW,		// â��â���� ����
	PLAYER,			// �÷��̾�(�κ�â)���� ����
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class TakeInOutGoldPopup : public GameEngineActor
{
private:	// member Var
	TakeInOutPopupType PopupType_;			// �˾� Ÿ��
	TakeInOutPopCreateType CreateType_;		// �˾� ���� Ÿ��
	int MaxHaveGole_;						// �ش� �˾��� ������ ��ü�� ������ ��差(�ִ�ġ)
	int CurHaveGold_;						// ��差(ȭ��ǥ�ÿ�)

private:
	GameEngineUIRenderer* Panel_;			// �ǳ� ������

	GameEngineUIRenderer* GoldText_;		// ���� ��差 �ؽ�Ʈ

	GameEngineUIRenderer* GoldUpBtn_;		// ��差���� ��ư ������
	GameEngineCollision* GoldUpBtnCol_;		// ��差���� ��ư �浹ü
	Button_State GoldUpBtn_State_;			// ��差���� ��ư ����
	GameEngineUIRenderer* GoldDownBtn_;		// ��差���� ��ư ������
	GameEngineCollision* GoldDownBtnCol_;	// ��差���� ��ư �浹ü
	Button_State GoldDownBtn_State_;		// ��差���� ��ư ����
	GameEngineUIRenderer* CloseBtn_;		// �˾�â���� ��ư ������
	GameEngineCollision* CloseBtnCol_;		// �˾�â���� ��ư �浹ü
	Button_State CloseBtn_State_;			// �˾�â���� ��ư ����
	GameEngineUIRenderer* ApprovedBtn_;		// �ش� �˾�Ÿ�Ժ� ���� ��ư ������
	GameEngineCollision* ApprovedCol_;		// �ش� �˾�Ÿ�Ժ� ���� ��ư �浹ü
	Button_State ApprovedBtn_State_;		// �ش� �˾�Ÿ�Ժ� ���� ��ư ����

private:


public:
	TakeInOutGoldPopup();
	~TakeInOutGoldPopup();

protected:		// delete constructer
	TakeInOutGoldPopup(const TakeInOutGoldPopup& _other) = delete;
	TakeInOutGoldPopup(TakeInOutGoldPopup&& _other) noexcept = delete;

private:		//delete operator
	TakeInOutGoldPopup& operator=(const TakeInOutGoldPopup& _other) = delete;
	TakeInOutGoldPopup& operator=(const TakeInOutGoldPopup&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void GoldUpButtonClick(GameEngineCollision* _Other);
	void GoldDownButtonClick(GameEngineCollision* _Other);
	void CloseButtonClick(GameEngineCollision* _Other);
	void ApprovedButtonClick(GameEngineCollision* _Other);

private: // �� ��ư ���
	void GoldUp();
	void GoldDown();
	void Close();
	void Approved();

public:
	void CreateTakePopup(TakeInOutPopupType _PopupType, TakeInOutPopCreateType _CreateType, const float4& _InitPos);
};


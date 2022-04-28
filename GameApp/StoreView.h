#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// â��â�� ���������� ��� ����
struct StoreViewInfo
{

};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;

class StoreView : public GameEngineActor
{
private:
	bool StoreViewActive_;								// â��â Ȱ��/��Ȱ�� Flags
	int StoredGold_;									// â�� ����� ������差
	int StoredMaxGold_;									// â�� ���尡���� ��� �ִ뷮

private: // �ǳڰ���
	GameEngineUIRenderer* StoreViewPanel_;				// â��â �ǳڷ�����
	GameEngineCollision* StoreViewPanelCol_;			// â��â �ǳ��浹ü(�÷��̾� �̵��Ǵ� üũ��)

private: // ������
	// ��岨�����˾� ����
	GameEngineUIRenderer* StoreGoldTakeOutPopBtn_;		// â�� ����� ������差 ������ �˾���ư ������
	GameEngineCollision* StoreGoldTakeOutPopColBtn_;	// â�� ����� ������差 ������ �˾���ư �浹ü
	Button_State StoreGoldTakeOutPopBtnState_;			// â�� ����� ������差 ������ �˾���ư ����

	// ��差 ����
	GameEngineUIRenderer* StoreGold_;					// â�� ����� ������差
	GameEngineUIRenderer* StoreMaxGold_;				// â�� ����� ��� �ִ뷮

private: // â�ݱ��ư ����
	GameEngineUIRenderer* CloseButton_;					// â��â �����ư
	GameEngineCollision* CloseBtnCol_;					// â��â �����ư �浹ü
	Button_State CloseBtnState_;						// â��â �����ư ����

private: // ������ ��ġ����
	StoreViewInfo StoreViewInfo_;						// â��â ����(�����ۺ������, �����۹�ġ����, ...)

public:
	StoreView();
	~StoreView();

protected:		// delete constructer
	StoreView(const StoreView& _other) = delete;
	StoreView(StoreView&& _other) noexcept = delete;

private:		//delete operator
	StoreView& operator=(const StoreView& _other) = delete;
	StoreView& operator=(const StoreView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void CloseButtonClick(GameEngineCollision* _Other);
	void GoldButtonClick(GameEngineCollision* _Other);
	void PrivateStoreViewActive();
	void GoldPopupViewActive();

public:
	void StoreViewOff();
	void StoreViewOn();

public:
	int StoredGoldAdd(int _Gold);
	int StoredGoldSub(int _Gold);
};


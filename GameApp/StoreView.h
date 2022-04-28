#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class StoreView : public GameEngineActor
{
private:
	bool StoreViewActive_;

private: // �ǳڰ���
	GameEngineUIRenderer* StoreViewPanel_;				// â��â �ǳڷ�����
	GameEngineCollision* StoreViewPanelCol_;			// â��â �ǳ��浹ü(�÷��̾� �̵��Ǵ� üũ��)

private: // �ؽ�Ʈ����
	GameEngineUIRenderer* StoreGold_;					// â�� ����� ���
	GameEngineUIRenderer* StoreMaxGold_;				// â�� ����� ��� �ִ뷮

private: // â�ݱ��ư ����
	GameEngineUIRenderer* CloseButton_;					// â��â �����ư
	GameEngineCollision* CloseBtnCol_;					// â��â �����ư �浹ü
	Button_State CloseBtnState_;						// â��â �����ư ����

private: // ������ ��ġ����


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
	void PrivateStoreViewActive();

public:
	void StoreViewOff();
	void StoreViewOn();
};


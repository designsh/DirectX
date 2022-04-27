#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class StoreView : public GameEngineActor
{
private: // �ǳڰ���
	GameEngineUIRenderer* StoreViewPanel_;				// â��â �ǳڷ�����
	GameEngineCollision* StoreViewPanelCol_;			// â��â �ǳ��浹ü(�÷��̾� �̵��Ǵ� üũ��)

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

public:
};


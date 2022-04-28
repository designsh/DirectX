#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class StoreView : public GameEngineActor
{
private:
	bool StoreViewActive_;

private: // 판넬관련
	GameEngineUIRenderer* StoreViewPanel_;				// 창고창 판넬렌더러
	GameEngineCollision* StoreViewPanelCol_;			// 창고창 판넬충돌체(플레이어 이동판단 체크용)

private: // 텍스트관련
	GameEngineUIRenderer* StoreGold_;					// 창고 저장용 골드
	GameEngineUIRenderer* StoreMaxGold_;				// 창고 저장용 골드 최대량

private: // 창닫기버튼 관련
	GameEngineUIRenderer* CloseButton_;					// 창고창 종료버튼
	GameEngineCollision* CloseBtnCol_;					// 창고창 종료버튼 충돌체
	Button_State CloseBtnState_;						// 창고창 종료버튼 상태

private: // 아이템 배치관련


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


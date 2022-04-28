#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 창고창의 보유아이템 목록 정보
struct StoreViewInfo
{

};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;

class StoreView : public GameEngineActor
{
private:
	bool StoreViewActive_;								// 창고창 활성/비활성 Flags
	int StoredGold_;									// 창고에 저장된 보유골드량
	int StoredMaxGold_;									// 창고에 저장가능한 골드 최대량

private: // 판넬관련
	GameEngineUIRenderer* StoreViewPanel_;				// 창고창 판넬렌더러
	GameEngineCollision* StoreViewPanelCol_;			// 창고창 판넬충돌체(플레이어 이동판단 체크용)

private: // 골드관련
	// 골드꺼내기팝업 관련
	GameEngineUIRenderer* StoreGoldTakeOutPopBtn_;		// 창고 저장용 보유골드량 꺼내기 팝업버튼 렌더러
	GameEngineCollision* StoreGoldTakeOutPopColBtn_;	// 창고 저장용 보유골드량 꺼내기 팝업버튼 충돌체
	Button_State StoreGoldTakeOutPopBtnState_;			// 창고 저장용 보유골드량 꺼내기 팝업버튼 상태

	// 골드량 관련
	GameEngineUIRenderer* StoreGold_;					// 창고 저장용 보유골드량
	GameEngineUIRenderer* StoreMaxGold_;				// 창고 저장용 골드 최대량

private: // 창닫기버튼 관련
	GameEngineUIRenderer* CloseButton_;					// 창고창 종료버튼
	GameEngineCollision* CloseBtnCol_;					// 창고창 종료버튼 충돌체
	Button_State CloseBtnState_;						// 창고창 종료버튼 상태

private: // 아이템 배치관련
	StoreViewInfo StoreViewInfo_;						// 창고창 정보(아이템보유목록, 아이템배치상태, ...)

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


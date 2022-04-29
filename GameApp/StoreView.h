#pragma once
#include <GameEngine/GameEngineActor.h>

#include "MainPlayerInfomation.h"
#include "GlobalEnumClass.h"

// 창고창의 아이템배치타일정보
class GameEngineUIRenderer;
struct StoredArrangeTileInfo
{
	bool ItemArrangementFlag_;								// 해당 타일의 배치완료 Flag(아이템이 배치되었다면 true)
	int Index_;												// 해당 타일의 총괄인덱스
	int IndexX_;											// 해당 타일의 X 인덱스
	int IndexY_;											// 해당 타일의 Y 인덱스
	float4 TileScale_;										// 해당 타일의 크기
	float4 TilePos_;										// 해당 타일의 위치
	GameEngineUIRenderer* TileRenderer_;					// 해당 타일의 렌더러(아이템 배치시 Blue Color)
};

// 가지고있는 아이템의 정보
class GameEngineUIRenderer;
struct StoredItem
{
	bool OneSize_;											// 해당 아이템의 크기가 1x1일때 true
	int StartIndex;											// 해당 아이템의 크기가 1x1일때 차지하는 인덱스
	std::vector<int> ArrangeIndexs_;						// 해당 아이템의 크기가 1x1이 아닐때 차지하는 인덱스목록
	ItemList ItemInfo_;										// 해당 아이템의 기본정보(이름, 판매금액, ...)
	float4 RenderPos_;										// 해당 아이템렌더러 위치
	GameEngineUIRenderer* ItemRenderer_;					// 해당 아이템 렌더러
};

// 창고창의 보유아이템 목록 정보
struct StoreViewInfo
{
	std::vector<StoredArrangeTileInfo> ArrangeTiles_;		// 배치타일정보
	std::vector<StoredItem> HaveItemList_;					// 보유하고있는 아이템목록
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class TakeInOutGoldPopup;
class StoreView : public GameEngineActor
{
private:
	bool StoreViewActive_;											// 창고창 활성/비활성 Flags
	int StoredGold_;												// 창고에 저장된 보유골드량
	int StoredMaxGold_;												// 창고에 저장가능한 골드 최대량

private: // 판넬관련
	GameEngineUIRenderer* StoreViewPanel_;							// 창고창 판넬렌더러
	GameEngineCollision* StoreViewPanelCol_;						// 창고창 판넬충돌체(플레이어 이동판단 체크용)

private: // 골드관련
	// 골드꺼내기팝업 관련
	GameEngineUIRenderer* StoreGoldTakeOutPopBtn_;					// 창고 저장용 보유골드량 꺼내기 팝업버튼 렌더러
	GameEngineCollision* StoreGoldTakeOutPopColBtn_;				// 창고 저장용 보유골드량 꺼내기 팝업버튼 충돌체
	Button_State StoreGoldTakeOutPopBtnState_;						// 창고 저장용 보유골드량 꺼내기 팝업버튼 상태

	// 골드량 관련
	GameEngineUIRenderer* StoreGold_;								// 창고 저장용 보유골드량
	GameEngineUIRenderer* StoreMaxGold_;							// 창고 저장용 골드 최대량

	// 골드팝업 관련
	TakeInOutGoldPopup* TakeOutGoldPopup_;							// 창고에 저장된 골드량 꺼내기 팝업창

private: // 창닫기버튼 관련
	GameEngineUIRenderer* CloseButton_;								// 창고창 종료버튼
	GameEngineCollision* CloseBtnCol_;								// 창고창 종료버튼 충돌체
	Button_State CloseBtnState_;									// 창고창 종료버튼 상태

private: // 아이템 배치관련
	StoreViewInfo StoreViewInfo_;									// 창고창 정보(아이템보유목록, 아이템배치상태, ...)
	std::vector<GameEngineCollision*> StoreArrTileCols_;			// 각 창고창의 배치타일 충돌체

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


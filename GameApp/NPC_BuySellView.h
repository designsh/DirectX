#pragma once
#include <GameEngine/GameEngineActor.h>
#include "AllNPCInfomation.h"
#include "GlobalEnumClass.h"

// 판매창의 아이템배치타일정보
class GameEngineUIRenderer;
struct ArrangeTileInfo
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
struct HaveItem
{
	bool OneSize_;											// 해당 아이템의 크기가 1x1일때 true
	int StartIndex;											// 해당 아이템의 크기가 1x1일때 차지하는 인덱스
	std::vector<int> ArrangeIndexs_;						// 해당 아이템의 크기가 1x1이 아닐때 차지하는 인덱스목록
	ItemList ItemInfo_;										// 해당 아이템의 기본정보(이름, 판매금액, ...)
	GameEngineUIRenderer* ItemRenderer_;					// 해당 아이템 렌더러
	float4 RenderPos_;										// 해당 아이템렌더러 위치
};

// 판매창의 탭정보
class GameEngineUIRenderer;
class GameEngineCollision;
struct TabInfo
{
	int TabIndex_;											// 탭 인덱스
	bool TabActive_;										// 탭 활성화여부(선택시 true)
	GameEngineUIRenderer* TabRenderer_;						// 탭 렌더러
	GameEngineCollision* TabCollision_;						// 탭 충돌체
	ItemLocType TabType_;									// 해당 탭의 타입(판매창 - 무기탭, 판매창 - 방어구탭, 판매창 - 기타탭)
	std::vector<ArrangeTileInfo> ArrangeTiles_;				// 해당 탭의 배치타일정보
	std::vector<HaveItem> HaveItemList_;					// 해당 탭이 보유하고있는 아이템목록
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class NPC_BuySellView : public GameEngineActor
{
private:
	static int CurTabIndex;									// 해당 판매창의 현재 탭인덱스

public:
	static int GetCurTabIndex();

private: // 판넬관련
	GameEngineUIRenderer* ViewPanel_;						// 판매창 판넬렌더러

private: // 버튼관련
	GameEngineUIRenderer* BuyButtonRenderer_;				// 구매 버튼 렌더러
	GameEngineCollision* BuyButtonCollider_;				// 구매 버튼 충돌체
	GameEngineUIRenderer* SellButtonRenderer_;				// 판매 버튼 렌더러
	GameEngineCollision* SellButtonCollider_;				// 판매 버튼 충돌체
	GameEngineUIRenderer* AllRepairButtonRenderer_;			// 전부수리 버튼 렌더러
	GameEngineCollision* AllRepairButtonCollider_;			// 전부수리 버튼 충돌체
	GameEngineUIRenderer* CloseButtonRenderer_;				// 창닫기 버튼 렌더러
	GameEngineCollision* CloseButtonCollider_;				// 창닫기 버튼 충돌체

private: // 탭정보관련
	std::vector<TabInfo> BuySellViewTabs_;					// 각 판매창의 탭정보(아이템목록, 배치상태, 인덱스, ...)

private: // 타일
	std::vector<GameEngineCollision*> ArrangeTileCols_;		// 각 판매창의 배치타일 충돌체

private: // NPC 타입 및 판매창 타입
	NPCClassType NPCClassType_;								// NPC 클래스 타입
	NPCType BuySellViewType_;								// 판매창타입

private:
	int HaveGold_;											// 해당 판매창(NPC)이 보유하고있는 골드
															// 1. 플레이어가 아이템구매시 해당 골드량증가
															// 2. 플레이어가 아이템판매시 해당 골드량감소

private: // 특수기능 버튼관련
	bool BuyActive_;										// 구매 활성화 Flag
	bool SellActive_;										// 판매 활성화 Flag
	bool AllRepairActive_;									// 전부수리 활성화 Flag
	Button_State BuyBtnState_;								// 구매버튼 상태
	Button_State SellBtnState_;								// 판매버튼 상태
	Button_State AllRepairBtnState_;						// 전부수리버튼 상태
	Button_State CloseBtnState_;							// 창닫기버튼 상태
	
public:
	NPC_BuySellView();
	~NPC_BuySellView();

protected:		// delete constructer
	NPC_BuySellView(const NPC_BuySellView& _other) = delete;
	NPC_BuySellView(NPC_BuySellView&& _other) noexcept = delete;

private:		//delete operator
	NPC_BuySellView& operator=(const NPC_BuySellView& _other) = delete;
	NPC_BuySellView& operator=(const NPC_BuySellView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private: // 각 버튼 클릭체크
	void BuyButtonClick(GameEngineCollision* _Other);
	void SellButtonClick(GameEngineCollision* _Other);
	void AllRepairButtonClick(GameEngineCollision* _Other);
	void CloseButtonClick(GameEngineCollision* _Other);

public: // 타입별 판매창 생성
	void CreateBuySellView(NPCType _BuySellViewType, NPCClassType _NPCClassType);

public: // 판매창 활성화/비활성화 처리
	void NPCBuySellViewActive();
	void NPCBuySellViewInactive();

public: // 판매창 탭과 충돌처리
	void SelectTabClick(GameEngineCollision* _Other, int _Index);

public: // 판매창 배치타일과 충돌처리
	void ArrangeTileClick(GameEngineCollision* _Other, int _Index);
};


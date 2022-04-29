#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 창의 타입
enum class TakeInOutPopupType
{
	NONE = -1,		// 생성시 초기화값
	TakeIn,			// 넣기
	TakeOut,		// 꺼내기
	Drop,			// 내려놓기
};

// 창을 생성한 객체의 타입
enum class TakeInOutPopCreateType
{
	NONE = -1,		// 생성시 초기화값
	STOREDVIEW,		// 창고창에서 생성
	PLAYER,			// 플레이어(인벤창)에서 생성
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class TakeInOutGoldPopup : public GameEngineActor
{
private:	// member Var
	TakeInOutPopupType PopupType_;					// 팝업 타입
	TakeInOutPopCreateType CreateType_;				// 팝업 생성 타입
	int MaxHaveGold_;								// 해당 팝업을 생성한 객체가 가지는 골드량(최대치)
	int CurHaveGold_;								// 골드량(화면표시용)

private:
	// 판넬 관련
	GameEngineUIRenderer* Panel_;					// 판넬 렌더러
	GameEngineCollision* TakeInOutPopCol_;			// 해당 창과 충돌중 어떠한 동작도 불가능하게 처리하기 위한 충돌체

	// 골드량 관련
	GameEngineUIRenderer* GoldText_;				// 현재 골드량 텍스트

	// 버튼 관련
	GameEngineUIRenderer* GoldUpBtn_;				// 골드량증가 버튼 렌더러
	GameEngineCollision* GoldUpBtnCol_;				// 골드량증가 버튼 충돌체
	Button_State GoldUpBtn_State_;					// 골드량증가 버튼 상태
	GameEngineUIRenderer* GoldDownBtn_;				// 골드량감소 버튼 렌더러
	GameEngineCollision* GoldDownBtnCol_;			// 골드량감소 버튼 충돌체
	Button_State GoldDownBtn_State_;				// 골드량감소 버튼 상태
	GameEngineUIRenderer* CloseBtn_;				// 팝업창종료 버튼 렌더러
	GameEngineCollision* CloseBtnCol_;				// 팝업창종료 버튼 충돌체
	Button_State CloseBtn_State_;					// 팝업창종료 버튼 상태
	GameEngineUIRenderer* ApprovedBtn_;				// 해당 팝업타입별 승인 버튼 렌더러
	GameEngineCollision* ApprovedCol_;				// 해당 팝업타입별 승인 버튼 충돌체
	Button_State ApprovedBtn_State_;				// 해당 팝업타입별 승인 버튼 상태

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

private: // 각 버튼 기능
	void GoldUp();
	void GoldDown();
	void Close();
	void Approved();

public:
	void CreateTakePopup(TakeInOutPopupType _PopupType, TakeInOutPopCreateType _CreateType, const float4& _InitPos, int _MaxGold);

public:
	void TakeInOutGoldPopupActive(int _CurHaveGold);
	void TakeInOutGoldPopupInactive();
};


#pragma once
#include <GameEngine/GameEngineActor.h>

enum class TakeInOutType
{
	NONE = -1,		// 생성시 초기화값
	TakeIn,			// 넣기
	TakeOut,		// 꺼내기
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class TakeInOutGoldPopup : public GameEngineActor
{
private:	// member Var
	TakeInOutType PopupType_;			// 팝업 타입
	int HaveGold_;						// 골드량

private:
	GameEngineUIRenderer* Panel_;		// 판넬 렌더러

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

public:
	void CreateTakePopup(TakeInOutType _PopupType, const float4& _InitPos);
};


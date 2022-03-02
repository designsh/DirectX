#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 관
// 용도 : 아이템 드랍 or 골드 드랍 or 몬스터 소환
// 설명 : 맵에 랜덤으로 배치되며, 타입에따라 텍스쳐가 결정된다.
//            또한, 마우스와 충돌하여 플레이어가 일정거리 진입시 애니메이션이 시작되며 애니메이션 마지막 프레임이 되면
//            랜덤으로 아이템 or 골드 드랍되거나, 몬스터가 소환된다.
//            이때 소환하는 몬스터는 Zombie로 고정
class GameEngineImageRenderer;
class CoffinObject : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Coffin_;

private:
	int CoffinType_; // 1 ~ 6의 타입이 존재하며 해당 타입에 따라 텍스쳐가 결정
	bool AnimationStart_;

public:
	CoffinObject();
	~CoffinObject();

protected:		// delete constructer
	CoffinObject(const CoffinObject& _other) = delete;
	CoffinObject(CoffinObject&& _other) noexcept = delete;

private:		//delete operator
	CoffinObject& operator=(const CoffinObject& _other) = delete;
	CoffinObject& operator=(const CoffinObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetCoffinType(int _CoffinType);
};


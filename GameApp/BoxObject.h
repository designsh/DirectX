#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 박스
// 용도 : 아이템 드랍 or 골드 드랍
// 설명 : 맵에 랜덤으로 배치되며, 타입에따라 텍스쳐가 결정된다.
//            또한, 마우스와 충돌하여 플레이어가 일정거리 진입시 애니메이션이 시작되며 애니메이션 마지막 프레임이 되면
//            랜덤으로 아이템 or 골드 드랍된다.
class GameEngineImageRenderer;
class BoxObject : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* BoxObject_;

private:
	int BoxType_;
	bool AnimationStart_;

public:
	BoxObject();
	~BoxObject();

protected:		// delete constructer
	BoxObject(const BoxObject& _other) = delete;
	BoxObject(BoxObject&& _other) noexcept = delete;

private:		//delete operator
	BoxObject& operator=(const BoxObject& _other) = delete;
	BoxObject& operator=(const BoxObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetBoxType(int _BoxType);
};


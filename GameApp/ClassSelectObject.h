#pragma once
#include <GameEngine/GameEngineActor.h>

#include "MainPlayerInfomation.h"

// 분류 : 애니메이션
// 용도 : 직업선택
// 설명 : 마우스와 충돌중이며 마우스 왼쪽버튼 클릭시 해당 직업(클래스)를 선택하는것으로 판단
class GameEngineImageRenderer;
class ClassSelectObject : public GameEngineActor
{
private:
	static JobType SelClassID;

public:
	static JobType GetSelectClass();

private:	// member Var
	GameEngineImageRenderer* ClassEntityRenderer_;
	GameEngineImageRenderer* ClassEffectRenderer_;

public:
	ClassSelectObject();
	~ClassSelectObject();

protected:		// delete constructer
	ClassSelectObject(const ClassSelectObject& _other) = delete;
	ClassSelectObject(ClassSelectObject&& _other) noexcept = delete;

private:		//delete operator
	ClassSelectObject& operator=(const ClassSelectObject& _other) = delete;
	ClassSelectObject& operator=(const ClassSelectObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void CreateClassRenderer(JobType _JobType, const float4& _Pos, const float4& _Size);
};


#pragma once
#include <GameEngine/GameEngineActor.h>

#include "MainPlayerInfomation.h"

enum class ClassRendererType
{
	ENTITY,
	EFFECT,
	MAX
};

enum class CurSelectState
{
	NotSel,
	SelStart,
	SelDefault,
	SelDeslect,
	MAX,
};

// 분류 : 애니메이션
// 용도 : 직업선택
// 설명 : 마우스와 충돌중이며 마우스 왼쪽버튼 클릭시 해당 직업(클래스)를 선택하는것으로 판단
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class MouseObject;
class ClassSelectObject : public GameEngineActor
{
private: // 해당 클래스를 사용하는 객체가 한개의 값을 가지도록 멤버전역변수로 선언 
	static JobType SelectClassType;

public:
	static JobType GetSelectClass();

private:	// member Var
	GameEngineImageRenderer* ClassRenderer[static_cast<int>(ClassRendererType::MAX)];
	GameEngineCollision* MainCollision_;

private:
	std::string TextureName_[static_cast<int>(CurSelectState::MAX)];

private:
	CurSelectState SelectState_;
	JobType JobType_;
	std::string JobName_;

private:
	GameEngineSoundPlayer* SelectSound_;

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
	void ChangeStartReset();

public:
	void DebugRender();

public:
	void CreateClassRenderer(const float4& _Pos, JobType _JobType = JobType::Necromancer, CurSelectState _FirstTextureType = CurSelectState::NotSel);

public:
	void DeSelectEnd();
	void SelectEnd();

public:
	void ClassSelOrDesel(GameEngineCollision* _OtherCollision);
	void CurClassSelect();
	void ChangeAnimation(CurSelectState _SelectType);
};


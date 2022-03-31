#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class SkillView : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* PanelRenderer_;						// ��ųâ �ǳ� ������

private:
	GameEngineUIRenderer* CloseButton_;							// ��ųâ �����ư ������
	GameEngineCollision* MainCollider_;							// ��ųâ �����ư �浹ü

private:
	Button_State ButtonState_;									// ��ư ����

public:
	SkillView();
	~SkillView();

protected:		// delete constructer
	SkillView(const SkillView& _other) = delete;
	SkillView(SkillView&& _other) noexcept = delete;

private:		//delete operator
	SkillView& operator=(const SkillView& _other) = delete;
	SkillView& operator=(const SkillView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void InitSkillView();
};


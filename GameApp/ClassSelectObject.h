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

// �з� : �ִϸ��̼�
// �뵵 : ��������
// ���� : ���콺�� �浹���̸� ���콺 ���ʹ�ư Ŭ���� �ش� ����(Ŭ����)�� �����ϴ°����� �Ǵ�
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class MouseObject;
class ClassSelectObject : public GameEngineActor
{
private: // �ش� Ŭ������ ����ϴ� ��ü�� �Ѱ��� ���� �������� ������������� ���� 
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


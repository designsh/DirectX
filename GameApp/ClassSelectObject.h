#pragma once
#include <GameEngine/GameEngineActor.h>

#include "MainPlayerInfomation.h"

// �з� : �ִϸ��̼�
// �뵵 : ��������
// ���� : ���콺�� �浹���̸� ���콺 ���ʹ�ư Ŭ���� �ش� ����(Ŭ����)�� �����ϴ°����� �Ǵ�
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


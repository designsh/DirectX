#include "PreCompile.h"
#include "BoneSpirit.h"

BoneSpirit::BoneSpirit() :
	Renderer_(nullptr),
	Collider_(nullptr),
	CurDir_(BoneSpirit_Dir::BS_L),
	StartPos_(float4::ZERO),
	TargetPos_(float4::ZERO)
{
}

BoneSpirit::~BoneSpirit()
{
}

void BoneSpirit::Start()
{
	// �ش� ��ų���� �ʱ�ȭ
	InitWizardProjectile();
}

void BoneSpirit::Update(float _DeltaTime)
{
}

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
	// 해당 스킬관련 초기화
	InitWizardProjectile();
}

void BoneSpirit::Update(float _DeltaTime)
{
}

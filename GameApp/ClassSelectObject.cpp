#include "PreCompile.h"
#include "ClassSelectObject.h"

#include <GameEngine/GameEngineImageRenderer.h>

JobType ClassSelectObject::SelClassID = JobType::None;

JobType ClassSelectObject::GetSelectClass()
{
	return SelClassID;
}

ClassSelectObject::ClassSelectObject() :
	ClassEntityRenderer_(nullptr),
	ClassEffectRenderer_(nullptr)
{
}

ClassSelectObject::~ClassSelectObject()
{
}

void ClassSelectObject::Start()
{
}

void ClassSelectObject::Update(float _DeltaTime)
{
	// ���콺�� �浹���̸�, ���콺 ���ʹ�ư Ŭ���� �ش� �������� ���õȴ�.
	// ���ý� SelectStartAnimation�� ����Ǹ�, ���������� ReleaseStartAnimation�� ����ȴ�.
	// ������������ Ŭ������ DefaultAnimation�� �����Ѵ�.
	// ����, ���� ������ ������ �����Ѵٸ� 'Ȯ��' ��ư�� Ȱ��ȭ�Ѵ�.


}

void ClassSelectObject::CreateClassRenderer(JobType _JobType, const float4& _Pos, const float4& _Size)
{
	std::string TextureName = "";
	std::string AnimationName = "";

	// ������ �̸� ����
	switch (_JobType)
	{
		case JobType::Necromancer:
		{
			// �ؽ��ĸ� ����
			TextureName = "Nec_";

			// 

			// �ִϸ��̼Ǹ� ����
			AnimationName = "Nec_";

			break;
		}
		case JobType::Amazon:
		{
			// �ؽ��ĸ� ����


			// �ִϸ��̼Ǹ� ����

			break;
		}
		case JobType::Sorceress:
		{
			// �ؽ��ĸ� ����


			// �ִϸ��̼Ǹ� ����

			break;
		}
		case JobType::Barbarian:
		{
			// �ؽ��ĸ� ����


			// �ִϸ��̼Ǹ� ����

			break;
		}
		case JobType::Paladin:
		{
			// �ؽ��ĸ� ����


			// �ִϸ��̼Ǹ� ����

			break;
		}
	}
}

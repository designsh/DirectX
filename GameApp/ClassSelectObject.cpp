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
	// 마우스와 충돌중이며, 마우스 왼쪽버튼 클릭시 해당 직업으로 선택된다.
	// 선택시 SelectStartAnimation이 실행되며, 선택해제시 ReleaseStartAnimation이 실행된다.
	// 선택하지않은 클래스는 DefaultAnimation을 실행한다.
	// 또한, 현재 선택한 직업이 존재한다면 '확인' 버튼을 활성화한다.


}

void ClassSelectObject::CreateClassRenderer(JobType _JobType, const float4& _Pos, const float4& _Size)
{
	std::string TextureName = "";
	std::string AnimationName = "";

	// 직업별 이름 편집
	switch (_JobType)
	{
		case JobType::Necromancer:
		{
			// 텍스쳐명 편집
			TextureName = "Nec_";

			// 

			// 애니메이션명 편집
			AnimationName = "Nec_";

			break;
		}
		case JobType::Amazon:
		{
			// 텍스쳐명 편집


			// 애니메이션명 편집

			break;
		}
		case JobType::Sorceress:
		{
			// 텍스쳐명 편집


			// 애니메이션명 편집

			break;
		}
		case JobType::Barbarian:
		{
			// 텍스쳐명 편집


			// 애니메이션명 편집

			break;
		}
		case JobType::Paladin:
		{
			// 텍스쳐명 편집


			// 애니메이션명 편집

			break;
		}
	}
}

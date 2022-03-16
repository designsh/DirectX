#include "PreCompile.h"
#include "ClassSelectObject.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineTransform.h>

#include "CurPlayerGameStartButton.h"
#include "MouseObject.h"

JobType ClassSelectObject::SelectClassType = JobType::None;

JobType ClassSelectObject::GetSelectClass()
{
	return SelectClassType;
}

ClassSelectObject::ClassSelectObject() :
	MainCollision_(nullptr),
	SelectState_(CurSelectState::MAX),
	JobType_(JobType::None),
	JobName_{}
{
	for (int i = 0; i < 2; ++i)
	{
		ClassRenderer[i] = nullptr;
	}
}

ClassSelectObject::~ClassSelectObject()
{
}

void ClassSelectObject::Start()
{
}

void ClassSelectObject::Update(float _DeltaTime)
{
	// 마우스와 충돌중이며, 마우스 왼쪽버튼 클릭시 해당 직업으로 선택 or 선택해제
	MainCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(OrderGroup::MouseCollider), std::bind(&ClassSelectObject::ClassSelOrDesel, this, std::placeholders::_1));

	GetLevel()->PushDebugRender(MainCollision_->GetTransform(), CollisionType::Rect);
}

void ClassSelectObject::CreateClassRenderer(const float4& _Pos, JobType _JobType, CurSelectState _FirstTextureType)
{
	// 본체															// 이펙트
	// Nec_Entity_NotSelDefault				// Nec_Effect_NotSelDefault
	// Nec_Entity_SelDefault						// Nec_Effect_SelDefault
	// Nec_Entity_SelDeslect						// Nec_Effect_SelDeslect
	// Nec_Entity_SelStart							// Nec_Effect_SelStart

	TextureName_[static_cast<int>(CurSelectState::NotSel)] = "_NotSelDefault";
	TextureName_[static_cast<int>(CurSelectState::SelStart)] = "_SelStart";
	TextureName_[static_cast<int>(CurSelectState::SelDefault)] = "_SelDefault";
	TextureName_[static_cast<int>(CurSelectState::SelDeslect)] = "_SelDeslect";

	// 직업별 이름 편집
	std::string EntityName = "";
	std::string EffectName = "";
	switch (_JobType)
	{
		case JobType::Necromancer:
		{
			JobName_ = "Nec_";
			EntityName = "Nec_Entity";
			EffectName = "Nec_Effect";
			break;
		}
		case JobType::Amazon:
		{
			JobName_ = "Ama_";
			EntityName = "Ama_Entity";
			EffectName = "Ama_Effect";
			break;
		}
		case JobType::Sorceress:
		{
			JobName_ = "Sor_";
			EntityName = "Sor_Entity";
			EffectName = "Sor_Effect";
			break;
		}
		case JobType::Barbarian:
		{
			JobName_ = "Bar_";
			EntityName = "Bar_Entity";
			EffectName = "Bar_Effect";
			break;
		}
		case JobType::Paladin:
		{
			JobName_ = "Pal_";
			EntityName = "Pal_Entity";
			EffectName = "Pal_Effect";
			break;
		}
	}

	// 직업지정이 되었다면 본체렌더러, 이펙트 렌더러 생성
	if (JobType::None != _JobType)
	{
		// ============================================== 본체 생성 ============================================== //
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)] = CreateTransformComponent<GameEngineImageRenderer>(static_cast<int>(OrderGroup::NormalObject0));
		
		std::string Entity_NotSelName = EntityName;
		Entity_NotSelName += TextureName_[static_cast<int>(CurSelectState::NotSel)];
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->CreateAnimation("Nec_Entity_NotSelDefault.png", Entity_NotSelName, 0, 11, 0.1f);

		std::string Entity_SelDefaultName = EntityName;
		Entity_SelDefaultName += TextureName_[static_cast<int>(CurSelectState::SelDefault)];
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->CreateAnimation("Nec_Entity_SelDefault.png", Entity_SelDefaultName, 0, 11, 0.1f);

		// 선택해제 애니메이션 종료시 선택되지않은 애니메이션으로 전환을 위해 Callback Function 지정
		std::string Entity_SelDeslectName = EntityName;
		Entity_SelDeslectName += TextureName_[static_cast<int>(CurSelectState::SelDeslect)];
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->CreateAnimation("Nec_Entity_SelDeslect.png", Entity_SelDeslectName, 0, 27, 0.1f, false);
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->SetEndCallBack(Entity_SelDeslectName, std::bind(&ClassSelectObject::DeSelectEnd, this));

		// 선택시작 애니메이션 종료시 선택된 애니메이션으로 전환을 위해 Callback Function 지정
		std::string Entity_SelStartName = EntityName;
		Entity_SelStartName += TextureName_[static_cast<int>(CurSelectState::SelStart)];
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->CreateAnimation("Nec_Entity_SelStart.png", Entity_SelStartName, 0, 37, 0.1f, false);
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->SetEndCallBack(Entity_SelStartName, std::bind(&ClassSelectObject::SelectEnd, this));

		// ============================================== 효과 생성 ============================================== //
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)] = CreateTransformComponent<GameEngineImageRenderer>(static_cast<int>(OrderGroup::NormalObject1));

		std::string Effect_NotSelName = EffectName;
		Effect_NotSelName += TextureName_[static_cast<int>(CurSelectState::NotSel)];
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->CreateAnimation("Nec_Effect_NotSelDefault.png", Effect_NotSelName, 0, 11, 0.1f);

		std::string Effect_SelDefaultName = EffectName;
		Effect_SelDefaultName += TextureName_[static_cast<int>(CurSelectState::SelDefault)];
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->CreateAnimation("Nec_Effect_SelDefault.png", Effect_SelDefaultName, 0, 11, 0.1f);

		std::string Effect_SelDeslectName = EffectName;
		Effect_SelDeslectName += TextureName_[static_cast<int>(CurSelectState::SelDeslect)];
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->CreateAnimation("Nec_Effect_SelDeslect.png", Effect_SelDeslectName, 0, 27, 0.1f, false);

		std::string Effect_SelStartName = EffectName;
		Effect_SelStartName += TextureName_[static_cast<int>(CurSelectState::SelStart)];
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->CreateAnimation("Nec_Effect_SelStart.png", Effect_SelStartName, 0, 37, 0.1f, false);

		// 최종
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->GetTransform()->SetLocalPosition(_Pos);
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));

		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalPosition(float4(_Pos.x, _Pos.y + 100.f));
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));

		std::string FirstEntityAni = EntityName;
		FirstEntityAni += TextureName_[static_cast<int>(_FirstTextureType)];

		std::string FirstEffectAni = EffectName;
		FirstEffectAni += TextureName_[static_cast<int>(_FirstTextureType)];

		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->SetChangeAnimation(FirstEntityAni);
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->SetChangeAnimation(FirstEffectAni);

		// ============================================= 충돌체 생성 ============================================= //
		MainCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(OrderGroup::NormalObject0_Collider));
		MainCollision_->GetTransform()->SetLocalScaling(float4(256.0f, 256.0f, 1.0f));

		// 현재 상태 저장
		SelectState_ = _FirstTextureType;
		JobType_ = _JobType;
	}
}

void ClassSelectObject::DeSelectEnd()
{
	// 선택해제 애니메이션 종료시 호출
	if (false == JobName_.empty())
	{
		std::string EntityAniName = JobName_;
		EntityAniName += "Entity";
		EntityAniName += TextureName_[static_cast<int>(CurSelectState::NotSel)];

		std::string EffectAniName = JobName_;
		EffectAniName += "Effect";
		EffectAniName += TextureName_[static_cast<int>(CurSelectState::NotSel)];

		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->SetChangeAnimation(EntityAniName);
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->SetChangeAnimation(EffectAniName);

		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalPosition(float4(0.f, 100.f));
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));

		SelectState_ = CurSelectState::NotSel;
	}
}

void ClassSelectObject::SelectEnd()
{
	// 선택시작 애니메이션 종료시 호출
	if (false == JobName_.empty())
	{
		std::string EntityAniName = JobName_;
		EntityAniName += "Entity";
		EntityAniName += TextureName_[static_cast<int>(CurSelectState::SelDefault)];

		std::string EffectAniName = JobName_;
		EffectAniName += "Effect";
		EffectAniName += TextureName_[static_cast<int>(CurSelectState::SelDefault)];

		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->SetChangeAnimation(EntityAniName);
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->SetChangeAnimation(EffectAniName);

		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalPosition(float4(0.f, 100.f));
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));

		SelectState_ = CurSelectState::SelDefault;
	}
}

void ClassSelectObject::ClassSelOrDesel(GameEngineCollision* _OtherCollision)
{
	// 충돌중 마우스왼쪽버튼 클릭시 해당 액터 애니메이션 상태 전환
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 해당 액터(직업클래스)의 선택/미선택 상태에 따라 애니메이션 변경처리
		// 선택 : 이전에 이미 선택된 클래스로 한번더 클릭시 선택해제 모션 시작 및 확인버튼 비활성화
		// 미선택 : 이전에 선택되지않은 클래스로 클릭시 선택 모션 시작 및 확인버튼 활성화
		CurClassSelect();
	}
}

void ClassSelectObject::CurClassSelect()
{
	bool ChangeFlag = false;

	std::string EntityName = JobName_;
	EntityName += "Entity";

	std::string EffectName = JobName_;
	EffectName += "Effect";

	// 현재 선택되었는지 체크
	switch (SelectState_)
	{
		case CurSelectState::NotSel:
		{
			// 현재 선택되지않은 상태라면 선택 시작 애니메이션으로 전환
			EntityName += TextureName_[static_cast<int>(CurSelectState::SelStart)];
			EffectName += TextureName_[static_cast<int>(CurSelectState::SelStart)];

			// 현재 상태 변경
			SelectState_ = CurSelectState::SelStart;

			// 선택했으므로 해당 직업타입을 넘긴다.
			SelectClassType = JobType_;

			// 확인버튼 활성화
			CurPlayerGameStartButton::UserClassSelect();
			break;
		}
		case CurSelectState::SelDefault:
		{
			// 현재 선택된 상태라면 선택해제 애니메이션으로 전환
			EntityName += TextureName_[static_cast<int>(CurSelectState::SelDeslect)];
			EffectName += TextureName_[static_cast<int>(CurSelectState::SelDeslect)];

			// 현재 상태 변경
			SelectState_ = CurSelectState::SelDeslect;

			// 선택해제 했으므로 선택하지않은 상태로 값을 넘긴다.
			SelectClassType = JobType::None;

			// 확인버튼 비활성화
			CurPlayerGameStartButton::UserClassDeselect();
			break;
		}
		case CurSelectState::SelDeslect:
		case CurSelectState::SelStart:
		{
			// 현재 선택해제 상태 or 선택시작 상태라면 무시
			ChangeFlag = true;
			break;
		}
	}

	if (false == ChangeFlag)
	{
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->SetChangeAnimation(EntityName);
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->SetChangeAnimation(EffectName);

		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalPosition(float4(0.f, 100.f));
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));
		ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));
	}
}

void ClassSelectObject::ChangeAnimation(CurSelectState _SelectState)
{
	std::string AnimationName = "";

	switch (JobType_)
	{
		case JobType::Necromancer:
		{
			AnimationName = "Nec_";
			break;
		}
		case JobType::Amazon:
		{
			AnimationName = "Ama_";
			break;
		}
		case JobType::Sorceress:
		{
			AnimationName = "Sor_";
			break;
		}
		case JobType::Barbarian:
		{
			AnimationName = "Bar_";
			break;
		}
		case JobType::Paladin:
		{
			AnimationName = "Pal_";
			break;
		}
	}

	// 본체 애니메이션 변경
	std::string EntityName = AnimationName;
	EntityName += "Entity";
	EntityName += TextureName_[static_cast<int>(_SelectState)];
	ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->SetChangeAnimation(EntityName);
	ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));

	// 이펙트 애니메이션 변경
	std::string EffectName = AnimationName;
	EffectName += "Effect";
	EffectName += TextureName_[static_cast<int>(_SelectState)];
	ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->SetChangeAnimation(EffectName);
	ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalPosition(float4(0.f, 100.f));
	ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));

	// 선택 상태 저장
	SelectState_ = _SelectState;
}

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
	// ���콺�� �浹���̸�, ���콺 ���ʹ�ư Ŭ���� �ش� �������� ���� or ��������
	MainCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(OrderGroup::MouseCollider), std::bind(&ClassSelectObject::ClassSelOrDesel, this, std::placeholders::_1));

	GetLevel()->PushDebugRender(MainCollision_->GetTransform(), CollisionType::Rect);
}

void ClassSelectObject::CreateClassRenderer(const float4& _Pos, JobType _JobType, CurSelectState _FirstTextureType)
{
	// ��ü															// ����Ʈ
	// Nec_Entity_NotSelDefault				// Nec_Effect_NotSelDefault
	// Nec_Entity_SelDefault						// Nec_Effect_SelDefault
	// Nec_Entity_SelDeslect						// Nec_Effect_SelDeslect
	// Nec_Entity_SelStart							// Nec_Effect_SelStart

	TextureName_[static_cast<int>(CurSelectState::NotSel)] = "_NotSelDefault";
	TextureName_[static_cast<int>(CurSelectState::SelStart)] = "_SelStart";
	TextureName_[static_cast<int>(CurSelectState::SelDefault)] = "_SelDefault";
	TextureName_[static_cast<int>(CurSelectState::SelDeslect)] = "_SelDeslect";

	// ������ �̸� ����
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

	// ���������� �Ǿ��ٸ� ��ü������, ����Ʈ ������ ����
	if (JobType::None != _JobType)
	{
		// ============================================== ��ü ���� ============================================== //
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)] = CreateTransformComponent<GameEngineImageRenderer>(static_cast<int>(OrderGroup::NormalObject0));
		
		std::string Entity_NotSelName = EntityName;
		Entity_NotSelName += TextureName_[static_cast<int>(CurSelectState::NotSel)];
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->CreateAnimation("Nec_Entity_NotSelDefault.png", Entity_NotSelName, 0, 11, 0.1f);

		std::string Entity_SelDefaultName = EntityName;
		Entity_SelDefaultName += TextureName_[static_cast<int>(CurSelectState::SelDefault)];
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->CreateAnimation("Nec_Entity_SelDefault.png", Entity_SelDefaultName, 0, 11, 0.1f);

		// �������� �ִϸ��̼� ����� ���õ������� �ִϸ��̼����� ��ȯ�� ���� Callback Function ����
		std::string Entity_SelDeslectName = EntityName;
		Entity_SelDeslectName += TextureName_[static_cast<int>(CurSelectState::SelDeslect)];
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->CreateAnimation("Nec_Entity_SelDeslect.png", Entity_SelDeslectName, 0, 27, 0.1f, false);
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->SetEndCallBack(Entity_SelDeslectName, std::bind(&ClassSelectObject::DeSelectEnd, this));

		// ���ý��� �ִϸ��̼� ����� ���õ� �ִϸ��̼����� ��ȯ�� ���� Callback Function ����
		std::string Entity_SelStartName = EntityName;
		Entity_SelStartName += TextureName_[static_cast<int>(CurSelectState::SelStart)];
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->CreateAnimation("Nec_Entity_SelStart.png", Entity_SelStartName, 0, 37, 0.1f, false);
		ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->SetEndCallBack(Entity_SelStartName, std::bind(&ClassSelectObject::SelectEnd, this));

		// ============================================== ȿ�� ���� ============================================== //
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

		// ����
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

		// ============================================= �浹ü ���� ============================================= //
		MainCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(OrderGroup::NormalObject0_Collider));
		MainCollision_->GetTransform()->SetLocalScaling(float4(256.0f, 256.0f, 1.0f));

		// ���� ���� ����
		SelectState_ = _FirstTextureType;
		JobType_ = _JobType;
	}
}

void ClassSelectObject::DeSelectEnd()
{
	// �������� �ִϸ��̼� ����� ȣ��
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
	// ���ý��� �ִϸ��̼� ����� ȣ��
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
	// �浹�� ���콺���ʹ�ư Ŭ���� �ش� ���� �ִϸ��̼� ���� ��ȯ
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// �ش� ����(����Ŭ����)�� ����/�̼��� ���¿� ���� �ִϸ��̼� ����ó��
		// ���� : ������ �̹� ���õ� Ŭ������ �ѹ��� Ŭ���� �������� ��� ���� �� Ȯ�ι�ư ��Ȱ��ȭ
		// �̼��� : ������ ���õ������� Ŭ������ Ŭ���� ���� ��� ���� �� Ȯ�ι�ư Ȱ��ȭ
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

	// ���� ���õǾ����� üũ
	switch (SelectState_)
	{
		case CurSelectState::NotSel:
		{
			// ���� ���õ������� ���¶�� ���� ���� �ִϸ��̼����� ��ȯ
			EntityName += TextureName_[static_cast<int>(CurSelectState::SelStart)];
			EffectName += TextureName_[static_cast<int>(CurSelectState::SelStart)];

			// ���� ���� ����
			SelectState_ = CurSelectState::SelStart;

			// ���������Ƿ� �ش� ����Ÿ���� �ѱ��.
			SelectClassType = JobType_;

			// Ȯ�ι�ư Ȱ��ȭ
			CurPlayerGameStartButton::UserClassSelect();
			break;
		}
		case CurSelectState::SelDefault:
		{
			// ���� ���õ� ���¶�� �������� �ִϸ��̼����� ��ȯ
			EntityName += TextureName_[static_cast<int>(CurSelectState::SelDeslect)];
			EffectName += TextureName_[static_cast<int>(CurSelectState::SelDeslect)];

			// ���� ���� ����
			SelectState_ = CurSelectState::SelDeslect;

			// �������� �����Ƿ� ������������ ���·� ���� �ѱ��.
			SelectClassType = JobType::None;

			// Ȯ�ι�ư ��Ȱ��ȭ
			CurPlayerGameStartButton::UserClassDeselect();
			break;
		}
		case CurSelectState::SelDeslect:
		case CurSelectState::SelStart:
		{
			// ���� �������� ���� or ���ý��� ���¶�� ����
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

	// ��ü �ִϸ��̼� ����
	std::string EntityName = AnimationName;
	EntityName += "Entity";
	EntityName += TextureName_[static_cast<int>(_SelectState)];
	ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->SetChangeAnimation(EntityName);
	ClassRenderer[static_cast<int>(ClassRendererType::ENTITY)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));

	// ����Ʈ �ִϸ��̼� ����
	std::string EffectName = AnimationName;
	EffectName += "Effect";
	EffectName += TextureName_[static_cast<int>(_SelectState)];
	ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->SetChangeAnimation(EffectName);
	ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalPosition(float4(0.f, 100.f));
	ClassRenderer[static_cast<int>(ClassRendererType::EFFECT)]->GetTransform()->SetLocalScaling(float4(256.f, 256.f, 1.f));

	// ���� ���� ����
	SelectState_ = _SelectState;
}

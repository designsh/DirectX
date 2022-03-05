#include "PreCompile.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"
#include "GameEngineTransform.h"

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

void GameEngineCollision::Start()
{
	GetLevel()->PushCollision(this, GetOrder());
}

void GameEngineCollision::Update(float _DeltaTime)
{
}

void GameEngineCollision::SetCollisionGroup(int _Type)
{
	GetLevel()->ChangeCollisionGroup(_Type, this);
}

void GameEngineCollision::Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::vector<GameEngineCollision*>& _ColVector)
{
	std::list<GameEngineCollision*>& Group = GetLevel()->GetCollisionGroup(_OtherGroup);

	DirectX::BoundingSphere ThisSphere;
	DirectX::BoundingSphere OtherSphere;

	float4 Pos = GetTransform()->GetWorldPosition();
	float4 Scale = GetTransform()->GetWorldScaling() * 0.5f;

	float4 OtherPos;
	float4 OtherScale;

	memcpy_s(&ThisSphere.Center, sizeof(ThisSphere.Center), &Pos, sizeof(ThisSphere.Center));
	memcpy_s(&ThisSphere.Radius, sizeof(float), &Scale, sizeof(float));

	for (GameEngineCollision* OtherCollision : Group)
	{
		OtherPos = OtherCollision->GetTransform()->GetWorldPosition();
		OtherScale = OtherCollision->GetTransform()->GetLocalScaling() * 0.5f;

		memcpy_s(&OtherSphere.Center, sizeof(ThisSphere.Center), &OtherPos, sizeof(ThisSphere.Center));
		memcpy_s(&OtherSphere.Radius, sizeof(float), &OtherScale, sizeof(float));

		if (false == ThisSphere.Intersects(OtherSphere))
		{
			continue;
		}

		_ColVector.push_back(OtherCollision);
	}
}

void GameEngineCollision::Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
	switch (_ThisType)
	{
		case CollisionType::Sphere:
		{
			switch (_OtherType)
			{
				case CollisionType::Sphere:
				{
					SphereToSphereCollision(_OtherGroup, _CallBack);
					break;
				}
				case CollisionType::AABBBox:
				{
					SphereToAABBBoxCollision(_OtherGroup, _CallBack);
					break;
				}
				case CollisionType::OBBBox:
				{
					SphereToOBBBoxCollision(_OtherGroup, _CallBack);
					break;
				}
				default:
				{
					GameEngineDebug::MsgBox("등록되지 않은 타입의 충돌방식입니다.!!!!");
					break;
				}
			}

			break;
		}
		case CollisionType::AABBBox:
		{
			switch (_OtherType)
			{
				case CollisionType::AABBBox:
				{
					AABBBoxToAABBBoxCollision(_OtherGroup, _CallBack);
					break;
				}
				case CollisionType::Sphere:
				{
					AABBBoxToSphereCollision(_OtherGroup, _CallBack);
					break;
				}
				case CollisionType::OBBBox:
				{
					AABBBoxToOBBBoxCollision(_OtherGroup, _CallBack);
					break;
				}
				default:
				{
					GameEngineDebug::MsgBox("등록되지 않은 타입의 충돌방식입니다.!!!!");
					break;
				}
			}

			break;
		}
		case CollisionType::OBBBox:
		{
			switch (_OtherType)
			{
				case CollisionType::OBBBox:
				{
					OBBBoxToOBBBoxCollision(_OtherGroup, _CallBack);
					break;
				}
				case CollisionType::Sphere:
				{
					OBBBoxToSphereCollision(_OtherGroup, _CallBack);
					break;
				}
				case CollisionType::AABBBox:
				{
					OBBBoxToAABBBoxCollision(_OtherGroup, _CallBack);
					break;
				}
				default:
				{
					GameEngineDebug::MsgBox("등록되지 않은 타입의 충돌방식입니다.!!!!");
					break;
				}
			}

			break;
		}
		default:
		{
			GameEngineDebug::MsgBox("등록되지 않은 타입의 충돌방식입니다.!!!!");
			break;
		}
	}
}

void GameEngineCollision::SphereToSphereCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
	std::list<GameEngineCollision*>& Group = GetLevel()->GetCollisionGroup(_OtherGroup);

	DirectX::BoundingSphere ThisSphere;
	DirectX::BoundingSphere OtherSphere;

	float4 Pos = GetTransform()->GetWorldPosition();
	float4 Scale = GetTransform()->GetWorldScaling() * 0.5f;

	float4 OtherPos;
	float4 OtherScale;

	memcpy_s(&ThisSphere.Center, sizeof(ThisSphere.Center), &Pos, sizeof(ThisSphere.Center));
	memcpy_s(&ThisSphere.Radius, sizeof(float), &Scale, sizeof(float));

	for (GameEngineCollision* OtherCollision : Group)
	{
		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		OtherPos = OtherCollision->GetTransform()->GetWorldPosition();
		OtherScale = OtherCollision->GetTransform()->GetLocalScaling() * 0.5f;

		memcpy_s(&OtherSphere.Center, sizeof(ThisSphere.Center), &OtherPos, sizeof(ThisSphere.Center));
		memcpy_s(&OtherSphere.Radius, sizeof(float), &OtherScale, sizeof(float));

		if (false == ThisSphere.Intersects(OtherSphere))
		{
			continue;
		}

		_CallBack(OtherCollision);
	}
}

void GameEngineCollision::SphereToAABBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
}

void GameEngineCollision::SphereToOBBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
}

void GameEngineCollision::AABBBoxToAABBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{



}

void GameEngineCollision::AABBBoxToSphereCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
}

void GameEngineCollision::AABBBoxToOBBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
}

void GameEngineCollision::OBBBoxToOBBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{




}

void GameEngineCollision::OBBBoxToSphereCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
}

void GameEngineCollision::OBBBoxToAABBBoxCollision(int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
}

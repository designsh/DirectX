#include "PreCompile.h"
#include "Andariel.h"

void Andariel::InitAndariel()
{
	// 몬스터정보 생성
	CreateInfomation();

	// 애니메이션 관련 텍스쳐 컷팅
	TextureCutting();

	// 애니메이션 생성관련
	CreateAnimation();

	// 애니메이션 종료시점 호출함수 관련
	CreateAnimationEndFunction();

	// FSM 상태관련
	CreateFSMState();

	// 충돌체 생성
	CreateCollision();
}

void Andariel::TextureCutting()
{




	//// 대기상태(Fallen_Idle.png, 20x8)
	//GameEngineTexture* Fallen_Idle = GameEngineTextureManager::GetInst().Find("Fallen_Idle.png");
	//Fallen_Idle->Cut(20, 8);

	//// 이동상태(Fallen_Walk.png, 10x8)
	//GameEngineTexture* Fallen_Walk = GameEngineTextureManager::GetInst().Find("Fallen_Walk.png");
	//Fallen_Walk->Cut(10, 8);

	//// 공격상태(Fallen_Attack.png, 10x8)
	//GameEngineTexture* Fallen_Attack = GameEngineTextureManager::GetInst().Find("Fallen_Attack.png");
	//Fallen_Attack->Cut(10, 8);

	//// 피격상태(Fallen_GetHit.png, 7x8)
	//GameEngineTexture* Fallen_GetHit = GameEngineTextureManager::GetInst().Find("Fallen_GetHit.png");
	//Fallen_GetHit->Cut(7, 8);

	//// 사망상태(Fallen_Death.png, 20x8)
	//GameEngineTexture* Fallen_Death = GameEngineTextureManager::GetInst().Find("Fallen_Death.png");
	//Fallen_Death->Cut(20, 8);

	//// 시체상태(Fallen_Dead.png, 8x1)
	//GameEngineTexture* Fallen_Dead = GameEngineTextureManager::GetInst().Find("Fallen_Dead.png");
	//Fallen_Dead->Cut(1, 8);
}

void Andariel::CreateAnimation()
{

}

void Andariel::CreateAnimationEndFunction()
{

}

void Andariel::CreateFSMState()
{

}

void Andariel::CreateCollision()
{

}

void Andariel::CreateInfomation()
{

}
#include "PreCompile.h"
#include "Andariel.h"

void Andariel::InitAndariel()
{
	// �������� ����
	CreateInfomation();

	// �ִϸ��̼� ���� �ؽ��� ����
	TextureCutting();

	// �ִϸ��̼� ��������
	CreateAnimation();

	// �ִϸ��̼� ������� ȣ���Լ� ����
	CreateAnimationEndFunction();

	// FSM ���°���
	CreateFSMState();

	// �浹ü ����
	CreateCollision();
}

void Andariel::TextureCutting()
{




	//// ������(Fallen_Idle.png, 20x8)
	//GameEngineTexture* Fallen_Idle = GameEngineTextureManager::GetInst().Find("Fallen_Idle.png");
	//Fallen_Idle->Cut(20, 8);

	//// �̵�����(Fallen_Walk.png, 10x8)
	//GameEngineTexture* Fallen_Walk = GameEngineTextureManager::GetInst().Find("Fallen_Walk.png");
	//Fallen_Walk->Cut(10, 8);

	//// ���ݻ���(Fallen_Attack.png, 10x8)
	//GameEngineTexture* Fallen_Attack = GameEngineTextureManager::GetInst().Find("Fallen_Attack.png");
	//Fallen_Attack->Cut(10, 8);

	//// �ǰݻ���(Fallen_GetHit.png, 7x8)
	//GameEngineTexture* Fallen_GetHit = GameEngineTextureManager::GetInst().Find("Fallen_GetHit.png");
	//Fallen_GetHit->Cut(7, 8);

	//// �������(Fallen_Death.png, 20x8)
	//GameEngineTexture* Fallen_Death = GameEngineTextureManager::GetInst().Find("Fallen_Death.png");
	//Fallen_Death->Cut(20, 8);

	//// ��ü����(Fallen_Dead.png, 8x1)
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
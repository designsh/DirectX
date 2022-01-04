#include "PreCompile.h"
#include "GameEngineObjectBase.h"

GameEngineObjectBase::GameEngineObjectBase() // default constructer ����Ʈ ������
	: isDeath_(false),
	isUpdate_(true),
	isDebug_(false), // ����� ��� �̰� true�� �س��� f9 �ɾ� ������ 
	parent_(nullptr)
{

}

GameEngineObjectBase::~GameEngineObjectBase() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineObjectBase::GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: isDeath_(_other.isDeath_),
	isUpdate_(_other.isUpdate_),
	isDebug_(_other.isDebug_), // ����� ��� �̰� true�� �س��� f9 �ɾ� ������ 
	parent_(_other.parent_)
{

}


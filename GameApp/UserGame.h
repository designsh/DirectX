#pragma once
#include <GameEngine/GameEngineCore.h>

// �з� : 
// �뵵 : 
// ���� : 
class UserGame : public GameEngineCore
{
private:	// member Var

public:
	UserGame(); // default constructer ����Ʈ ������
	~UserGame(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	UserGame(const UserGame& _other) = delete; // default Copy constructer ����Ʈ ���������
	UserGame(UserGame&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	UserGame& operator=(const UserGame& _other) = delete; // default Copy operator ����Ʈ ���� ������
	UserGame& operator=(const UserGame&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	virtual void Initialize() override;
	virtual void ResourcesLoad() override;
	virtual void GameLoop() override;
	virtual void Release() override;
	virtual float4 StartWindowPos() override;
	virtual float4 StartWindowSize() override;
};


#pragma once
#include "GameEnginePath.h"
// �з� :
// �뵵 :
// ���� :

class GameEngineFile;
class GameEngineDirectroy : public GameEnginePath
{
public:
	GameEngineDirectroy(); // default constructer ����Ʈ ������
	~GameEngineDirectroy(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineDirectroy(const GameEngineDirectroy& _other); // default Copy constructer ����Ʈ ���������
	GameEngineDirectroy(GameEngineDirectroy&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineDirectroy& operator=(const GameEngineDirectroy& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineDirectroy& operator=(const GameEngineDirectroy&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	std::string DirectroyName();

public:		//member Func
	bool IsRoot();
	void MoveParent();
	bool MoveParent(const std::string& _DirName);
	bool MoveChild(const std::string& _DirName);

public:
	std::string PathToPlusFileName(const std::string& _DirName);
	GameEngineFile PathToCreateFile(const std::string& _FileName);
	GameEngineFile PathToGetFile(const std::string& _FileName);
};


#pragma once
#include "GameEnginePath.h"

// �з� : ���͸�(����) ����
// �뵵 : 
// ���� : �ش� ������ ���� �������͸���ΰ��� �� ���͸� �̵���� ����
class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	GameEngineDirectory(); // default constructer ����Ʈ ������
	~GameEngineDirectory(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineDirectory(const GameEngineDirectory& _other); // default Copy constructer ����Ʈ ���������
	GameEngineDirectory(GameEngineDirectory&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineDirectory& operator=(const GameEngineDirectory& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineDirectory& operator=(const GameEngineDirectory&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	std::string DirectoryName();
	bool IsRoot();
	void MoveParent();
	bool MoveParent(const std::string& _DirName);
	bool MoveChild(const std::string& _DirName);

public:
	std::string PathToPlusFileName(const std::string& _DirName);
	std::vector<GameEngineFile> GetAllFile(const std::string& _filter = "*", bool _AllDirectory = false);
};


#pragma once
#include "GameEnginePath.h"

// 분류 : 디렉터리(폴더) 관리
// 용도 : 
// 설명 : 해당 파일이 속한 최종디렉터리경로관리 및 디렉터리 이동기능 제공
class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	GameEngineDirectory(); // default constructer 디폴트 생성자
	~GameEngineDirectory(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineDirectory(const GameEngineDirectory& _other); // default Copy constructer 디폴트 복사생성자
	GameEngineDirectory(GameEngineDirectory&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineDirectory& operator=(const GameEngineDirectory& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineDirectory& operator=(const GameEngineDirectory&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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


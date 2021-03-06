#pragma once

// 분류 : 경로관리
// 용도 : 경로관리
// 설명 : GameEngineFile의 객체가 해당 클래스를 상속받아 해당 파일의 경로를 관리
class GameEnginePath
{
public:
	static std::string GetFileName(std::string _Path);

protected:	// member Var
	std::filesystem::path path_;

public:		
	GameEnginePath(); // default constructer 디폴트 생성자
	GameEnginePath(std::filesystem::path _path);
	~GameEnginePath(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEnginePath(const GameEnginePath& _other); // default Copy constructer 디폴트 복사생성자
	GameEnginePath(GameEnginePath&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEnginePath& operator=(const GameEnginePath& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEnginePath& operator=(const GameEnginePath&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	bool IsExist();	// 유효한 경로인가 아닌가를 판단하는 함수.
	std::string GetFullPath();

public:
	std::string GetFileName();
	std::string GetFileNameWithOutExtension();
	std::string GetExtension();
};

